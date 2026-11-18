void reverse(char *str) {
    int length = 0;
    char *ptr = str;
    
    // Calculate the length of the string
    while (*ptr != '\0') {
        length++;
        ptr++;
    }
    
    // Reverse the string in place
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}