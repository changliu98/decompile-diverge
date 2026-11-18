void Reverse(char *str) {
    int left = 0;
    int right = 0;
    char temp;

    // Find the length of the string
    while (str[right] != '\0') {
        right++;
    }
    
    // Point to the last valid character
    right--;

    // If the string ends with a newline, ignore it
    if (str[right] == '\n') {
        right--;
    }

    // Swap characters from the outside in
    while (left < right) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        
        right--;
        left++;
    }
}