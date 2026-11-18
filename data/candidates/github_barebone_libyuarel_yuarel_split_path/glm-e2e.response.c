int yuarel_split_path(char *path, char **components, int max_components) {
    int count = 0;
    int ret;

    if (path == NULL || *path == '\0') {
        ret = -1;
    } else {
        while (1) {
            // Skip leading slashes
            while (*path == '/') {
                path++;
            }

            // Check if we reached the end of the string
            if (*path == '\0') {
                break;
            }

            // Store the current component pointer
            components[count++] = path;

            // Find the next slash
            path = strchr(path, '/');

            // If no more slashes, we are done
            if (path == NULL) {
                break;
            }

            // Terminate the current component and move to the next character
            *path = '\0';
            path++;

            // Stop if we've reached the maximum number of components
            if (count < max_components) {
                continue;
            } else {
                break;
            }
        }
        ret = count;
    }

    return ret;
}