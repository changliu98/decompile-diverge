char *ft_strcpy(char *dest, char *src) {
  int len_dest;
  int len_src;
  int i;
  len_dest = 0;
  while (dest[len_dest++])
    ;
  len_src = 0;
  while (src[len_src++])
    ;
  i = -1;
  if (len_src > len_dest) return ("");
  while (src[++i]) dest[i] = src[i];
  dest[i] = '\0';
  return (dest);
}