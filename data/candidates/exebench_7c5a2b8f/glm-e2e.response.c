char* pat_strcpy(char* dest, const char* src) {
    char *p = dest;
    while ((*p++ = *src++) != '\0') {
        // empty loop body
    }
    return p - 1;
}