void strcpymax(char *dest, const char *src, int n)
{
 int i;
 for (i = 0; i < n && *src != '\0'; i++)
  *dest++ = *src++;
 *dest = '\0';
}