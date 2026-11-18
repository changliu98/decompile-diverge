char* func0(char* input) {
    static char result_string[100];
    char buf[100];
    int j = 0;
    
    memset(buf, 0, 100);
    
    /* Collect all vowels from input into buf */
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (strchr("aeiouAEIOU", c) != NULL) {
            buf[j++] = c;
        }
    }
    
    j = 0;
    int k = strlen(buf) - 1;
    
    /* Build result: reverse vowels, keep other chars in place */
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (strchr("aeiouAEIOU", c) != NULL) {
            result_string[j++] = buf[k--];
        } else {
            result_string[j++] = input[i];
        }
    }
    result_string[j] = '\0';
    
    return result_string;
}