int hex_to_int(char *str, int *num) {
    int i;
    int flag;

    *num = 0;
    i = 0;
    while (i < 9) {
        if (str[i] >= '0' && str[i] <= '9')
            *num = *num * 16 + str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f')
            *num = *num * 16 + str[i] - 'a' + 10;
        else
            break;
        i++;
    }
    if (i == 9)
        flag = 1;
    else
        flag = 0;
    return (flag);
}