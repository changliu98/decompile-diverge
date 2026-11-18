static char *base91(char *s, int n)
{
 *s++ = (n / 91) + 33;
 *s++ = (n % 91) + 33;
 return s;
}