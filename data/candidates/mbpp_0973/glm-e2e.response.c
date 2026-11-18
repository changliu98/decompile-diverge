char *func0(const char *str, int shift) {
    int len = strlen(str);
    char *result = malloc(len + 1);
    
    for (int i = 0; i < len; i++) {
        result[i] = str[(i + shift) % len];
    }
    result[len] = '\0';
    
    return result;
}