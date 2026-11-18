char *uwsgi_expand_path(char *path, int path_len, char *resolved_path) {
    char local_path[0x1030];
    char *resolved_ptr;
    char *result;

    // Copy the input path to a local buffer and null-terminate it
    memcpy(local_path, path, path_len);
    local_path[path_len] = '\0';

    // If no output buffer is provided, allocate one
    resolved_ptr = resolved_path;
    if (resolved_ptr == NULL) {
        resolved_ptr = uwsgi_malloc(0x1001); // 4097 bytes
    }

    // Resolve the absolute pathname
    if (realpath(local_path, resolved_ptr) == NULL) {
        uwsgi_log("unable to retrieve %s path: %s\n", local_path, strerror(errno));
        
        // If we allocated the buffer ourselves, free it on failure
        if (resolved_path == NULL) {
            free(resolved_ptr);
        }
        result = NULL;
    } else {
        result = resolved_ptr;
    }

    return result;
}