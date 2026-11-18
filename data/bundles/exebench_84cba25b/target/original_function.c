char *base91(char *p, int i)
{
        *p++ = (i/91) + 33;
        *p++ = i % 91 + 33;

        return p;
}