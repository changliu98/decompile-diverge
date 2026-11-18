void reverse(char *str) {
    int i = 0;
    char temp;
    
    // Find the length of the string (until null terminator or newline)
    while (str[i] != '\0' && str[i] != '\n') {
        i++;
    }
    
    int j = i - 1;
    i = 0;
    
    // Reverse the string in place
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}