int func0(char *str) {
    int len = strlen(str);
    int i;
    int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
    for (i = 0; i < len; i++) {
        if (i < len) {
            if (isalpha(str[i]))
                flag1 = 1;
            else if (isdigit(str[i]))
                flag2 = 1;
            else if (ispunct(str[i]))
                flag3 = 1;
            else if (str[i] == '$' || str[i] == '#' || str[i] == '@')
                flag4 = 1;
            else if (isspace(str[i]))
                flag4 = 0;
        }
    }
    if (flag1 && flag2 && flag3 && flag4)
        return 1;
    else
        return 0;
}