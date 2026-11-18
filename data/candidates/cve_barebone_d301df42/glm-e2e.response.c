int call_backend(const char *cmd, int mode, struct backend_info *backend, struct data_info *data) {
    char local_cmd[1024];
    char command_buffer[65536];
    int status;
    char *env_val;
    char *colon_ptr;

    // Copy the command to a local buffer and ensure null termination
    strncpy(local_cmd, cmd, 1023);
    if (strlen(cmd) > 1023) {
        local_cmd[1023] = '\0';
    }

    // Strip everything after the first colon
    colon_ptr = strchr(local_cmd, ':');
    if (colon_ptr != NULL) {
        *colon_ptr = '\0';
    }

    // Check environment variable, fallback to default if not set
    env_val = getenv("SOME_ENV_VAR"); // String at 0x2048
    if (env_val == NULL) {
        env_val = "default_val";      // String at 0x2057
    }

    // Validate command prefix
    if (strncasecmp(cmd, "test:", 5) == 0 || cmd[0] == '/') {
        fprintf(stderr, "Invalid command\n"); // String at 0x206b
        exit(1);
    }

    // Format the command string based on the mode
    if (mode == 6) {
        snprintf(command_buffer, 65536, 
                 "fmt_str %s %s %s %p %p %p %s %p %p", // String at 0x20a1
                 env_val, 
                 local_cmd, 
                 backend->field_0x08, 
                 backend->field_0x10, 
                 backend->field_0x18, 
                 "mode_6_str",       // String at 0x20cb
                 backend->field_0x20, 
                 backend->field_0x28, 
                 data);
    } else {
        snprintf(command_buffer, 65536, 
                 "fmt_str %s %s %p %p %p %s %p %p",   // String at 0x20a1
                 env_val, 
                 local_cmd, 
                 backend->field_0x08, 
                 backend->field_0x10, 
                 backend->field_0x18, 
                 backend->field_0x20, 
                 backend->field_0x28, 
                 data);
    }

    // Set an environment variable
    setenv("ENV_VAR", cmd, 1); // String at 0x20cd

    // Log the command being executed
    fprintf(stderr, "Executing: %s\n", command_buffer); // String at 0x20d8
    fprintf(stderr, "For: %s\n", cmd);                  // String at 0x210c

    // Execute the command
    status = system(command_buffer) >> 8;

    // Handle system() failure
    if (status == -1) {
        fprintf(stderr, "system() failed: %s\n", strerror(errno)); // String at 0x212e
    }

    return status;
}