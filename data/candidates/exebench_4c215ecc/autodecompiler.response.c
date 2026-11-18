char *stpcpy0(char *s1, char *s2)
{
    while (1) {
 if (*s2 == '\0') {
     *s1 = '\0';
     return s1;
 }
 *s1++ = *s2++;
    }
}