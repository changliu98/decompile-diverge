void cwk_path_get_root_windows(const char *path, size_t *length) {
    const char *current;

    *length = 0;
    current = path;

    // Return if the path is empty
    if (*current == '\0') {
        return;
    }

    // Check if the path starts with a separator (e.g., "\" or "/")
    if (cwk_path_is_separator(current)) {
        current++;
        
        // Check if it's a UNC path (e.g., "\\server\share")
        if (cwk_path_is_separator(current)) {
            current++;
            
            // Check for special device paths like "\\.\"
            bool is_device = false;
            if (*current == '?' || *current == '.') {
                current++;
                is_device = cwk_path_is_separator(current);
            }
            
            if (is_device) {
                *length = 4;
                return;
            }
            
            // Skip over the server name
            current = cwk_path_find_next_stop(current);
            while (cwk_path_is_separator(current)) {
                current++;
            }
            
            // Skip over the share name
            current = cwk_path_find_next_stop(current);
            while (cwk_path_is_separator(current)) {
                current++;
            }
            
            // Calculate the length of the UNC root
            *length = current - path;
            return;
        } else {
            // It's a root separator like "\" or "/"
            *length = 1;
            return;
        }
    } else {
        // Check if it starts with a drive letter (e.g., "C:")
        if (cwk_path_is_drive_letter(current)) {
            *length = 2;
            current += 2;
            
            // Check for a separator following the drive letter (e.g., "C:\")
            if (cwk_path_is_separator(current)) {
                *length = 3;
            }
            return;
        }
    }
}