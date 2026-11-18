void tagcpy(char *dst, const char *src, int len) {
    const char *start = src;
    const char *end = src + len - 1;

    // Adjust the end pointer if it points to a null character 
    // or if the preceding character is not a null character.
    if (*end != '\0' || *(end - 1) != '\0') {
        end--;
    }

    // Skip leading spaces
    while (start <= end) {
        if (*start == ' ') {
            start++;
        } else if (*end == '\0' || *end == ' ') {
            end--;
        } else {
            break;
        }
    }

    // Copy the trimmed string to the destination
    while (*start != '\0' && start <= end) {
        *dst++ = *start++;
    }
    
    // Null-terminate the destination string
    *dst = '\0';
}