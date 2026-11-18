void shift_array(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        str[i] += 5;
        i++;
    }
}