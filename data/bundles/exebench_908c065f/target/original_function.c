void reverse(char *s)
{
    char *s0 = s;
    while (*s)
      s++;
    char c;
    s--;
    while (s0 < s)
    {
        c = *s0;
        *s0 = *s;
        *s = c;
        s0++, s--;
    }
}