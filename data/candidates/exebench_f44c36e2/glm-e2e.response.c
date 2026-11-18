char* strcpymax(char *dest, const char *src, int n) {
    char *original_dest = dest;
    int i = 0;

    if (n != 0) {
        n--; // Reserve space for the null terminator

        while (src[i] != '\0' && i < n) {
            dest[i] = src[i];
            i++;
        }
    }

    dest[i] = '\0'; // Guarantee null termination
    return original_dest;
}