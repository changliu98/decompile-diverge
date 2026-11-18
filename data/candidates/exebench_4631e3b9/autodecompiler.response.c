int c_decrypt(char *s)
{
 int c;

 while (*s) {
  c = *s - 13;
  if (c <= 0)
   c += 256;
  *s = c;
  s++;
 }
 return 0;
}