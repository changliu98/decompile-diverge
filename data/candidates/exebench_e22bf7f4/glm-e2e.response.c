void reverse(char *str) {
    int i = 0;
    int length = 0;
    char temp;

    // Calculate the length of the string
    while (str[i] != '\0') {
        i++;
        length++;
    }

    // Reset index for the swapping loop
    i = 0;

    // Reverse the string in place
    while (i < length / 2) {
        temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
        i++;
    }
}