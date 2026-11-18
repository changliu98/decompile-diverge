Assuming a sufficiently large buffer size based on the relative addressing

char* func0(const char* arg) {
    int j = 0;
    for (int i = 1; i <= strlen(arg); i++) {
        if (i % 2 != 0) {
            func0_str2[j++] = arg[i - 1];
        }
    }
    func0_str2[j] = '\0';
    return func0_str2;
}