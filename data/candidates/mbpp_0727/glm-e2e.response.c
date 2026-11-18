Approximate size based on typical BSS allocations

char *func0(const char *str) {
    int count = 0;
    int i = 0;
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            result[count++] = str[i];
        }
    }
    result[count] = '\0';
    return result;
}