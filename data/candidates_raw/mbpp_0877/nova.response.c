void func0(char *str) {
    int len = strlen(str);
    int i = 0, j;
    char temp;
    while (i < len - 1) {
        j = i + 1;
        while (j < len) {
            if (str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
            j++;
        }
        i++;
    }
}