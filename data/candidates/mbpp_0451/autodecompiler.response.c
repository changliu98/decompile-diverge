char *func0(char *s)
{
 int i = 0, j = 0;

 while (1) {
  if (s[i] == '\0')
   break;
  if (!((*___ctype_b_loc ())[(unsigned char)(s[i])] & (int)0x2000)) {
   s[j++] = s[i];
  }
  i++;
 }
 s[j] = '\0';
 return s;
}