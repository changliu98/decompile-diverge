void ulimit_stack(long *current_limit, long *max_limit, int *error_code)
{
    rlimit resource_limits;
    int set_result;

    // Set initial stack resource limits to predefined constants
    resource_limits.rlim_cur = DAT_00102008;
    resource_limits.rlim_max = DAT_00102010;
    
    // Attempt to set the new stack resource limits
    set_result = setrlimit(RLIMIT_STACK, &resource_limits);
    
    // If setting limits fails, try to set current limit to max limit
    if (set_result == -1) {
        // Get current limits to check if adjustment is possible
        if (getrlimit(RLIMIT_STACK, &resource_limits) == 0) {
            // Set current limit equal to maximum limit
            resource_limits.rlim_cur = resource_limits.rlim_max;
            // Retry setting the limits with adjusted values
            set_result = setrlimit(RLIMIT_STACK, &resource_limits);
        }
    }
    
    // Store the result of the last setrlimit operation
    *error_code = set_result;
    
    // Retrieve the final stack resource limits
    if (getrlimit(RLIMIT_STACK, &resource_limits) == 0) {
        // Successfully retrieved limits, store them in output parameters
        *current_limit = resource_limits.rlim_cur;
        *max_limit = resource_limits.rlim_max;
    } else {
        // Failed to retrieve limits, set output parameters to error value
        *current_limit = -1;
        *max_limit = -1;
    }
}