void unscramble(char *c)
{
 while (*c) {
  if (*c == 'p' || *c == '\\' || *c == 'S')
   ;
  else
   *c ^= 15;
  c++;
 }
}