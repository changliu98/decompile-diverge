char* strcpy_(char* dest, char* src) {
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return dest;
}