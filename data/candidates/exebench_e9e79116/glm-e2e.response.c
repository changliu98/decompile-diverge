void itoa(int num, char *str) {
    int i = 7;
    str[i] = '\0';
    
    do {
        str[--i] = (num % 10) + '0';
        num /= 10;
    } while (num != 0);
}