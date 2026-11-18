void reverse(char *str) {
    char *left = str;
    char *right = str;
    char temp1;
    char temp2;

    // Find the end of the string
    while (*right != '\0') {
        right++;
    }
    
    // Step back to the last character before the null terminator
    right--;

    // Swap characters from the outside in
    while (left < right) {
        temp1 = *left;
        temp2 = *right;
        *left = temp2;
        *right = temp1;
        
        left++;
        right--;
    }
}