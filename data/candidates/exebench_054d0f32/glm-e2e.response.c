char *my_strupcase(char *str) {
    char *result;

    if (str == 0) {
        result = 0;
    } else {
        int i = 0;
        while (str[i] != 0) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                str[i] = str[i] - 32;
            }
            i++;
        }
        result = str;
    }
    
    return result;
}