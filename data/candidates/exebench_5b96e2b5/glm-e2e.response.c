void reverse(char *str) {
    char *left = str;
    char *right = str;
    char temp;

    // Find the end of the string
    while (*right != '\0') {
        right++;
    }
    
    // Step back one character to the last non-null character
    right--;

    // Swap characters from the outside in
    while (left < right) {
        temp = *left;
        *left = *right;
        *right = temp;
        
        left++;
        right--;
    }
}