#define _GNU_SOURCE

#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_info.h"

void merge(struct proc_info *arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    struct proc_info L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i].memsize <= R[j].memsize) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 

    // return arr;
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
// struct proc_info* mergeSort(struct proc_info *arr, int l, int r) 
void mergeSort(struct proc_info *arr, int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r);
    } 

} 

 void printProcesses(){
    int maxElements = 64;
    struct proc_info *processesToSort = malloc(maxElements*sizeof(struct proc_info));
    int N = getprocs(maxElements, processesToSort);
    int i = 0;

    mergeSort(processesToSort, 0, N - 1);
    printf(1, "Starting\n");
    for(; i < N; i++) {
      printf(1,"name : %s, pid : %d, memory size : %d, state : %d \n", processesToSort[i].name, processesToSort[i].pid, processesToSort[i].memsize, processesToSort[i].state);
    }
    free(processesToSort);
 }


int main() {
  printf(1, "testing getprocs syscall\n");
  if (fork()==0)
  {
    if(fork()==0)
    {
      sleep(100);
      char * v = malloc(sizeof(char)*100000);
      for(char* i=v;i<v+50000;i++)
        *i = 'a';
      sleep(200);
      exit();
    }
    else{
    sleep(100);
    char * v = malloc(sizeof(char)*50000);
    for(char* i=v;i<v+50000;i++)
      *i = 'a';
    sleep(200);
    wait();
    exit();
    }
  }

  else
  {
    sleep(10);
    printProcesses();
    sleep(220);
    printProcesses();
    printf(1,"as you can see the memory size of the child has increased and are sorted in ascending order\n");
    wait();
    
    exit();
  }
 }

