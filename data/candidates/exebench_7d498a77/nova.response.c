int get_priority(pid_t pid, int *status) {
    *status = waitpid(pid, (int *)status, 0);
    return errno;
}