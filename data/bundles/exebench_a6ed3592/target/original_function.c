static void intToString(int n, char *str)
{
    if(n == 0) {
        str[0] = '0';
        str[1] = 0;
    } else {
        int i = 0;
        for(int t = n; t; t /= 10, ++i);

        str[i] = 0;
        --i;
        for(int t = n; i >= 0; --i, t /= 10) {
            str[i] = (t % 10) + '0';
        }
    }
}