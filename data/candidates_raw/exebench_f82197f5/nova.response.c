void func0(int *lock) {
    int c;
    int old, new;

    do {
        old = *lock;
        new = old - 1;
    } while (atomic_cmpset_int(lock, old, new) == 0);

    if (new == 1) {
        c = 0;
        while (c!= 2) {
            c = *lock;
            *lock = c;
            syscall(SYS_cpuset, CPU_SET_SINGLE, c, 1);
        }
    }
}