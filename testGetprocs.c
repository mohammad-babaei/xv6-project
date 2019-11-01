#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_info.h"

 void printProcesses(){
    int maxElements = 64;
    struct proc_info *processes = malloc(maxElements*sizeof(struct proc_info));
    int N = getprocs(maxElements, processes);
    int i = 0;
    printf(1, "Starting\n");
    for(; i < N; i++) {
      printf(1,"name : %s, pid : %d, memory size : %d, state : %d \n", processes[i].name, processes[i].pid, processes[i].memsize, processes[i].state);
    }
    free(processes);
 }


int main() {
  printf(1, "testing getprocs syscall\n");
  if (fork()==0)
  {
    sleep(100);
    char * v = malloc(sizeof(char)*50000);
    for(char* i=v;i<v+50000;i++)
      *i = 'a';
    sleep(200);
    exit();
  }

  else
  {
    sleep(10);
    printProcesses();
    sleep(220);
    printProcesses();
    printf(1,"as you can see the memory size of the child has increased\n");
    wait();
    
    exit();
  }
  
  //printf(1, "we have an array of processes using 'malloc(maxElements*sizeof(struct proc_info));' maxElements's value is: %d, size of proc_info is : %d and total size of process is : %d\n", maxElements, sizeof(struct proc_info), maxElements*sizeof(struct proc_info));

  // exit();
 }

