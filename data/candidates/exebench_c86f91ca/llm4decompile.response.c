void remove_dupc2(char *str)
{
    int i, j;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == -1)
            continue;
        for (j = i + 1; str[j] != '\0'; j++) {
            if (str[i] == str[j])
                str[j] = -1;
        }
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == -1)
            continue;
        break;
    }

    if (str[i] == '\0')
        i--;

    for (j = i + 1; str[j] != '\0'; j++) {
        if (str[j] == -1)
            continue;
        str[i++] = str[j];
    }
    str[i] = str[j];
}