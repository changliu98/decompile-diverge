void func0(char *str, char *str2) {
    int i = 0, j = 0;
    while (str[i]!= '\0') {
        if (isspace(str[i]) == 0) {
            str2[j++] = str[i];
        }
        i++;
    }
    str2[j] = '\0';
}