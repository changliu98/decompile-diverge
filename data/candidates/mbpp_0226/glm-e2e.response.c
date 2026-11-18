located at 0x4090

char* func0(const char* str) {
    int count = 0;
    int i = 0;
    
    while (i < strlen(str)) {
        if (i % 2 == 0) {
            result[count++] = str[i];
        }
        i++;
    }
    
    result[count] = '\0';
    return result;
}