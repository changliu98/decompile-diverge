void itoa(unsigned short n, char *s)
{
    unsigned short i, j;
    char tmp[16];

    if(n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    for(i=0; n!=0; ++i) {
        tmp[i] = n%10 + '0';
        n /= 10;
    }
    j = i;

    while(i != 0) {
        s[j-i] = tmp[i-1];
        --i;
    }
    s[j] = '\0';
}