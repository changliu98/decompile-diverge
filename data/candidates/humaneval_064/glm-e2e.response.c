int func0(const char *str) {
    const char *vowels = "aeiouAEIOU";
    int count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (strchr(vowels, str[i]) != NULL) {
            count++;
        }
    }
    
    if (len > 0) {
        if (str[len - 1] == 'y' || str[len - 1] == 'Y') {
            count++;
        }
    }
    
    return count;
}