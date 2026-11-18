Representing the global variable at 0x4090

char* func0(const char* str) {
    int j = 0;
    for (int i = 1; i <= strlen(str); i++) {
        if (i % 2 == 0) {
            func0_str[j++] = str[i - 1];
        }
    }
    func0_str[j] = '\0';
    return func0_str;
}