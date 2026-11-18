char zhalfstr(char *s)
{
    char lastchar, curchar, nextchar;
    int index, back, nonzero;

    lastchar = curchar = '0';
    index = -1;
    back = nonzero = 0;

    while (curchar != 0) {
        nextchar = s[index+1];
        s[index+1-back] = '0' + (nextchar-'0')/2 + (curchar-'0')%2 * 5;
        if (s[index+1-back] == '0' && nonzero == 0)
            back++;
        else
            nonzero = 1;
        if (curchar != 0)
            lastchar = curchar;
        curchar = nextchar;
        index++;
    }

    if (back == index) {
        s[0] = '0';
        s[1] = 0;
    }
    else
        s[index-back] = 0;

    return lastchar;
}