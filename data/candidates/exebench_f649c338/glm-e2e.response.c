char *ft_strrev(char *str) {
    int i = 0;
    int j = 0;
    char temp;

    // Find the length of the string
    while (str[i] != '\0') {
        i++;
    }
    
    // Set i to the index of the last character
    i--;

    // Swap characters from the outside in
    while (i > j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i--;
        j++;
    }

    return str;
}