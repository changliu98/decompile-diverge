void strcatc(char *str, unsigned long *len, unsigned long maxlen, char c)
{
  if ( *len < maxlen )
    str[*len] = c;
  (*len)++;
}