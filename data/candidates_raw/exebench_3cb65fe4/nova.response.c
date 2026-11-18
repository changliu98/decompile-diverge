char *func0(char *s, int *num) {
    int i = 0, n = 1, numb = 0;
    bool sign;
    while (true) {
        sign = true;
        if (s[i] == '+')
            sign = true;
        else if (s[i] == '-')
            sign = false;
        else
            break;
        if (sign) {
            if (s[i] == '-')
                numb = numb * (-1);
        }
        i++;
    }
    *num = numb;
    return s + i;
}