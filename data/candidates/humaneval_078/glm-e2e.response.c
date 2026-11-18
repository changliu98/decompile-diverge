int func0(const char *str) {
    const char *vowels = "aeiouAEIOU";
    int count = 0;
    int i = 0;
    
    while (i < strlen(str)) {
        if (strchr(vowels, str[i]) != NULL) {
            count++;
        }
        i++;
    }
    
    return count;
}