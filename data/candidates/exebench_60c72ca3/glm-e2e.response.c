void string_rip(char *src, const char *rip_chars) {
    char *dest = src;

    while (*src != '\0') {
        const char *r = rip_chars;
        bool found = false;

        // Check if the current character is in the rip_chars string
        while (*r != '\0') {
            if (*src == *r) {
                found = true;
                break;
            }
            r++;
        }

        if (found) {
            // If the character should be removed, just advance the source pointer
            src++;
        } else {
            // Otherwise, copy the character to the destination pointer
            *dest = *src;
            src++;
            dest++;
        }
    }

    // Null-terminate the modified string
    *dest = '\0';
}