static char *encode_11(char *s, int n)
{
 *s++ = (n / 91) + 33;
 *s++ = (n % 91) + 33;
 return s;
}