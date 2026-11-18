void remove_all_chars(char *str, char c)
{
    char *pw,*pr;

    pw = pr = str;
    while(*pr) {
        *pw = *pr;
        pw += (*pw != c);
        pr++;
    }
    *pw = '\0';
}