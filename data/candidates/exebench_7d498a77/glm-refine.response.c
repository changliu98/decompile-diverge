int __cdecl get_priority(long pid, int *priority)
{
    // PRIO_PROCESS (0) indicates we are querying a specific process ID
    *priority = getpriority(PRIO_PROCESS, (id_t)pid);
    
    // Return the thread-local errno value directly as the function's return code
    return errno;
}