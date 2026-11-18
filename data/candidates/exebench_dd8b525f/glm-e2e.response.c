void reverse(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    i--;
    if (str[i] == '\n') {
        i--;
    }
    
    int j = 0;
    while (j < i) {
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        i--;
        j++;
    }
}