void wdc_UtilsDeleteCharFromString(char *str, int size, char c) {
    int i, j;
    char is_duplicate;

    if (!str ||!size)
        return;

    for (i = j = 0; i < size; i++) {
        is_duplicate = (i > 0 && str[i] == str[i - 1])? 1 : 0;

        if (!is_duplicate) {
            if (str[i]!= c)
                str[j++] = str[i];
        }
    }
    str[j] = '\0';
}