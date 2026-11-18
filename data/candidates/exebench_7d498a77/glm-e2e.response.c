int get_priority(int which, int *priority) {
    *priority = getpriority(0, which);
    return errno;
}