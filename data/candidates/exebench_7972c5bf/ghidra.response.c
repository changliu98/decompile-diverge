void tagcpy(char *dest,char *src,int tag_size)

{
  char *s2;
  char *s1;
  int tag_size_local;
  char *src_local;
  char *dest_local;
  
  s2 = src + (long)tag_size + -1;
  s1 = src;
  if ((*s2 != '\0') && (src[(long)tag_size + -2] == '\0')) {
    s2 = src + (long)tag_size + -2;
  }
  while (dest_local = dest, s1 <= s2) {
    if (*s1 == ' ') {
      s1 = s1 + 1;
    }
    else {
      if ((*s2 != '\0') && (*s2 != ' ')) break;
      s2 = s2 + -1;
    }
  }
  while (*s1 != '\0' && s1 <= s2) {
    *dest_local = *s1;
    s1 = s1 + 1;
    dest_local = dest_local + 1;
  }
  *dest_local = '\0';
  return;
}