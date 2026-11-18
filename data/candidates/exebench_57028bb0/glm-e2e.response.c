char *ft_strcpy(char *dest, const char *src) {
    size_t dest_len = 0;
    while (dest[dest_len++] != '\0') {
        // Loop to find the length of dest
    }

    size_t src_len = 0;
    while (src[src_len++] != '\0') {
        // Loop to find the length of src
    }

    // If dest is smaller than src, return an error string
    if (dest_len < src_len) {
        return "Error";
    }

    long i = -1;
    while (src[++i] != '\0') {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return dest;
}