void strupr(char *str) {
    if (*str!= '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;
        } else {
            str++;
        }
    }
}