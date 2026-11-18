char *strcpy(char *dest, const char *src) {
    long i = 0;
    do {
        dest[i] = src[i];
        i++;
    } while (src[i - 1] != '\0');
    
    return dest;
}