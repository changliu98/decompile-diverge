void func0(char *str) {
    if (*str!= '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;
        } else {
            *str = *str + 32;
        }
        func0(str + 1);
    }
}