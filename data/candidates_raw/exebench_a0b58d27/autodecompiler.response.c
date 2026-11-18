char *strcpy(char *dest, const char *src)
{
    char *d;
    char *s;
    char *returnval;

    if (!src || !dest) {
 returnval = ((void *)0);
    } else {
 s = (char *)src;
 d = dest;
 while (*s != '\0') {
     *d++ = *s++;
 }
 *d = '\0';
 returnval = dest;
    }
    return returnval;
}