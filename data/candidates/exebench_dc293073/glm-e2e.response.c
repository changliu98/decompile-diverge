char* Q_strupr(char* s) {
    char* p = s;
    while (*p != '\0') {
        if (*p >= 'a' && *p <= 'z') {
            *p -= 32; // 0xffffffe0 is -32 in signed 32-bit, converting lowercase to uppercase
        }
        p++;
    }
    return s;
}