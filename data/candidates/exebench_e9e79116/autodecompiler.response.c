void itoa(unsigned int n, char *s)
{
    int pos = 7;
    s[pos] = '\0';
    do {
        s[pos--] = '0' + (n % 10);
        n /= 10;
    } while (n != 0);
}