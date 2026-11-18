void func0(int num, int base, char *str) {
    int i = 0;
    while (num > 0) {
        int rem = num % base;
        char c = rem + '0';
        str[i] = c;
        i++;
        num = num / base;
    }
    
    int j = 0;
    while (i > 0) {
        i--;
        str[j] = str[i];
        j++;
    }
    
    str[j] = '\0';
}