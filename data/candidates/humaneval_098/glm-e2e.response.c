int func0(const char *str) {
    const char *vowels = "aeiouAEIOU";
    int count = 0;
    int i = 0;
    
    while (str[i] != '\0' && (i * 2) < strlen(str)) {
        if (strchr(vowels, str[i * 2]) != NULL) {
            count++;
        }
        i++;
    }
    
    return count;
}