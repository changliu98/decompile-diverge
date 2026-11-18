char* str_rev(char* str) {
    char* left = str;
    char* right = str;
    char temp;

    // Find the end of the string
    while (*right != '\0') {
        right++;
    }

    // Step back twice to point to the last character
    right--;
    right--;

    // Swap characters from the outside in
    while (left <= right) {
        temp = *left;
        *left = *right;
        left++;
        *right = temp;
        right--;
    }

    return str;
}