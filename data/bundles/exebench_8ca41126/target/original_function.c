char
zhalfstr(char *s)
{
    char curchar = '0', nextchar;
    char outchar, lastchar = '0';
    int index = -1, nonzero = 0, back = 0;

    while (curchar != '\0') {
        nextchar = *(s + index + 1);
        outchar = (nextchar - '0') >> 1;
        outchar += 5 * (curchar & 1) + '0';
        *(s + index + 1 - back) = outchar;
        if (outchar == '0' && nonzero == 0)
            back++;
        else nonzero = 1;
        if (curchar != '\0')
            lastchar = curchar;
        curchar = nextchar;
        index++;
    }
    if (index == back) {
        *s = '0';
        *(s + 1) = 0;
    }
    else
        *(s + index - back) = 0;
    return lastchar;
}