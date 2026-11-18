char *func0(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    int min_len;
    if (len1 < len2) {
        min_len = len1;
    } else {
        min_len = len2;
    }
    
    char *result = (char *)malloc(min_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < min_len; i++) {
        if (str1[i] == str2[i]) {
            result[i] = '1';
        } else {
            result[i] = '0';
        }
    }
    
    result[min_len] = '\0';
    return result;
}