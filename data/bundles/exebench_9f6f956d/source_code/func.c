
int

ckstrncpy(char * dest, const char * src, int len)



{
    int i;
    if (len < 1 || !src || !dest) {
 if (dest) *dest = '\0';
 return(0);
    }

    for (i = 0; src[i] && (i < len-1); i++)
      dest[i] = src[i];
    dest[i] = '\0';






    return(i);
}
