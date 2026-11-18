int func0(char *str)
{
    int i;
    int len = strlen(str);

    for (i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return 0;
        }
    }

    return 1;
}