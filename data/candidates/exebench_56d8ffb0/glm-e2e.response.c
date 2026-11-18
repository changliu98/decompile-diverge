void wdc_UtilsDeleteCharFromString(char *str, int size, char char_to_delete) {
    int i = 0;
    int j = 0;

    if (str == NULL || size == 0) {
        return;
    }

    while (i < size && str[i] != '\0') {
        if (str[i] != char_to_delete) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    
    str[j] = '\0';
}