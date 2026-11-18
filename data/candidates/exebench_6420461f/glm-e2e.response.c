void ulimit_stack(rlim_t *soft_limit, rlim_t *hard_limit, int *result) {
    struct rlimit original_limits;
    struct rlimit new_limits;
    int ret;

    // Save the original limits
    getrlimit(RLIMIT_STACK, &original_limits);

    // Set the new limits provided by the caller
    new_limits.rlim_cur = *soft_limit;
    new_limits.rlim_max = *hard_limit;
    
    ret = setrlimit(RLIMIT_STACK, &new_limits);

    // If setrlimit failed, attempt to restore the original limits
    if (ret == -1) {
        if (getrlimit(RLIMIT_STACK, &new_limits) == 0) {
            new_limits.rlim_max = original_limits.rlim_max;
            ret = setrlimit(RLIMIT_STACK, &new_limits);
        }
    }

    // Update the caller's pointers with error status and reset limits
    *result = ret;
    *soft_limit = (rlim_t)-1; // 0xffffffffffffffff
    *hard_limit = (rlim_t)-1; // 0xffffffffffffffff

    // Fetch the actual current limits and update the caller's pointers on success
    if (getrlimit(RLIMIT_STACK, &new_limits) == 0) {
        *soft_limit = new_limits.rlim_cur;
        *hard_limit = new_limits.rlim_max;
    }
}