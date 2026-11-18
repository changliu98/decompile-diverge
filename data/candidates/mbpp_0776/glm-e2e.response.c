int func0(const char *str) {
    int count = 0;
    const char *vowels = "aeiouAEIOU";
    int len = strlen(str);
    
    for (int i = 1; i < len - 1; i++) {
        if (strchr(vowels, str[i]) == NULL) {
            if (strchr(vowels, str[i - 1]) != NULL || strchr(vowels, str[i + 1]) != NULL) {
                count++;
            }
        }
    }
    
    if (strchr(vowels, str[0]) == NULL && strchr(vowels, str[1]) != NULL) {
        count++;
    }
    
    if (strchr(vowels, str[len - 1]) == NULL && strchr(vowels, str[len - 2]) != NULL) {
        count++;
    }
    
    return count;
}