char* stringCopy(char* dest, char* src) {
    while (1) {
        char c = *src;
        *dest = c;
        if (c == '\0') {
            break;
        }
        dest++;
        src++;
    }
    return dest;
}