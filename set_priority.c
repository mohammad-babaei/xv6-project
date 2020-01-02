#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"


int main(int argc, char const *argv[])
{
    int old_priority;
    // the argv[1] is the pid and argv[2] is the priority
    int first_arg = atoi(argv[1]);
    int second_arg = atoi(argv[2]);
    // printf(1, "The first arg: %d . the second :%d\n", first_arg, second_arg);
    old_priority = set_priority(&second_arg, &first_arg);
    printf(1, "The old priority of process pid: %d is %d\n", first_arg, old_priority);
    exit();
}
