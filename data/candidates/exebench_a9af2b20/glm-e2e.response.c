char* stpCpy(char* dest, const char* src) {
    while ((*dest++ = *src++) != '\0') {
        // The loop body is empty; all work is done in the condition
    }
    return dest;
}