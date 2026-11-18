void string_reverse(char *str) {
    char *left = str;
    char *right = str;

    // Find the end of the string (null terminator)
    while (*right != '\0') {
        right++;
    }

    // Swap characters from the outside in
    while (left < right) {
        char temp = *left;
        right--;
        *left = *right;
        left++;
        *right = temp;
    }
}