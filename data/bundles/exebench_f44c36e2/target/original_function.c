void strcpymax(char *dest, const char *src, int n)
{
    int i;
    if (n) {
 n--;
 for (i = 0; *src && (i < n); i++)
     *dest++ = *src++;
    }
    *dest = 0;
}