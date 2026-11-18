int tt_unesc(char *str, char esc_char) {
    char *ptr = str;
    char *dest = NULL;
    int count = 0;

    // Find the first occurrence of the escape character
    while (*ptr != esc_char) {
        if (*ptr == 0) {
            return 0;
        }
        ptr++;
    }

    dest = ptr;

    // Process the string from the first escape character onwards
    while (*ptr != 0) {
        if (*ptr == esc_char) {
            ptr++;
            count++;
        }
        
        // Copy the current character and advance both pointers
        *dest = *ptr;
        dest++;
        ptr++;
    }

    return count;
}