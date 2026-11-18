void _uc(char *str) {
    if (*str!= '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;
        } else {
            *str = *str + 32;
        }
        _uc(str + 1);
    }
}