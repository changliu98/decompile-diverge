int
ckstrncpy(char *dest, const char *src, int len)
{
    int i;

    if (len > 0 && src != NULL && dest != NULL) {
 for (i = 0; src[i] != '\0' && i < len - 1; i++)
     dest[i] = src[i];
 dest[i] = '\0';
    } else {
 if (dest != NULL)
     dest[0] = '\0';
 i = 0;
    }
    return i;
}