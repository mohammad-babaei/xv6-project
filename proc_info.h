enum procstate2 { UNUSED3, EMBRYO3, SLEEPING3, RUNNABLE3, RUNNING3, ZOMBIE3 };

struct proc_info {
    int pid;
    uint memsize;
    char name[16];
    enum procstate2 state;

 };