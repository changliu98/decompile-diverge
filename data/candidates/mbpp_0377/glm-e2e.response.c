char *func0(const char *str, char c) {
    int count = 0;
    int i = 0;
    
    // First loop: count how many times the character 'c' appears in 'str'
    while (str[i] != '\0') {
        if (str[i] == c) {
            count++;
        }
        i++;
    }
    
    // Allocate memory for the new string.
    // Size is length of 'str' minus occurrences of 'c' plus 1 for the null terminator.
    char *result = (char *)malloc(strlen(str) - count + 1);
    
    int j = 0;
    i = 0;
    
    // Second loop: copy characters that are not equal to 'c'
    while (str[i] != '\0') {
        if (str[i] != c) {
            result[j] = str[i];
            j++;
        }
        i++;
    }
    
    // Null-terminate the new string
    result[j] = '\0';
    
    return result;
}