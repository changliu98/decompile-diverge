void dopr_outch(char *str, unsigned long *len, unsigned long maxlen, char c)
{
  if ( *len < maxlen )
    str[*len] = c;
  (*len)++;
}