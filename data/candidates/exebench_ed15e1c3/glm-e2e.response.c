void reverse(char *str) {
    int i = 0;
    int len = 0;
    char temp;

    // Calculate the length of the string
    while (str[i] != '\0') {
        i++;
    }
    len = i;

    // Reverse the string in place
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}