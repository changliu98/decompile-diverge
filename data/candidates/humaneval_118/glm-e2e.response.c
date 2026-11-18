char *func0(const char *str) {
    const char *vowels = "aeiouAEIOU";
    int len = strlen(str);
    int i = len - 2;
    
    while (i >= 0) {
        if (strchr(vowels, str[i]) != NULL) {
            if (strchr(vowels, str[i + 1]) == NULL && 
                strchr(vowels, str[i - 1]) == NULL) {
                out[0] = str[i];
                return out;
            }
        }
        i--;
    }
    
    out[0] = '\0';
    return out;
}