void ToRNA(char *str) {
    if (*str!= '\0') {
        if (*str == 'T')
            *str = 'U';
        else if (*str == 't')
            *str = 'u';
        else
            return ToRNA(++str);
    }
    return;
}