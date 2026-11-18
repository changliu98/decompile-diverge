void func0(char *str)
{
    int i, j, len;
    char temp;

    len = strlen(str);

    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (str[j] < str[i]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}