void itoa(short int num, char *str) {
    short int i = 0;
    short int len;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    len = i;
    
    // Reverse the string in-place
    while (i > 0) {
        i--;
        str[len - i - 1] = str[i];
    }
    
    str[len] = '\0';
}