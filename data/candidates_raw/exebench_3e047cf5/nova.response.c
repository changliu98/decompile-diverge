void func0(char *str) {
    if (*str!= '\0') {
        if (*str == 'T')
            *str = 'U';
        else if (*str == 't')
            *str = 'u';
        else
            return func0(++str);
    }
    return;
}