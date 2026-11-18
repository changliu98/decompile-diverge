int func0(char *str)
{
    int len = strlen(str);
    char tmp[len * 2 + 1];
    strcpy(tmp, str);
    strcat(tmp, str);

    int i;
    for (i = 1; i <= len; i++) {
        int j;
        int equal = 1;
        for (j = 0; j < len; j++) {
            if (str[j] != tmp[i + j]) {
                equal = 0;
                break;
            }
        }
        if (equal) {
            break;
        }
    }

    return i;
}