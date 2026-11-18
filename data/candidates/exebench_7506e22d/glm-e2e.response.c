void toup(char *str) {
    char diff = 32; // 0x20
    if (*str >= 'a' && *str <= 'z') {
        *str = *str - diff;
    }
}