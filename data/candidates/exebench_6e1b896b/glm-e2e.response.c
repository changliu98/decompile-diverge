char* break_at(char* str, char c) {
    char* ptr = strchr(str, c);
    if (ptr != NULL) {
        *ptr = '\0';
    }
    return ptr;
}