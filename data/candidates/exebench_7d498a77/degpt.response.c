// Retrieves the priority of the process specified by pid.
// Stores the retrieved priority value in the memory location pointed to by priority.
// Returns the errno value set by getpriority (0 on success, or an error code on failure).
int get_priority(long process_id, int *priority_value)
{
    // Call getpriority to fetch the priority of the process identified by pid.
    // The result is stored in the variable pointed to by priority.
    *priority_value = getpriority(PRIO_PROCESS, (id_t)process_id);
    
    // Return the errno value, which indicates success (0) or the specific error that occurred.
    return errno;
}