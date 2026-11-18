int get_priority(long pid, int *priority)
{
    *priority = getpriority(PRIO_PROCESS, pid);
    return errno;
}