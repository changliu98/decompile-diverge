int get_hex(char *s, int *val)
{
 int done, i = 0;

 *val = 0;
 for(;;) {
  if (!(!done ? 1 : 0)) break;
  if ((('0' <= s[i]) && (s[i] <= '9'))) {
   *val <<= 4;
   *val += s[i] - '0';
  } else if ((('A' <= s[i]) && (s[i] <= 'F'))) {
   *val <<= 4;
   *val += s[i] - 'A' + 10;
  } else if ((('a' <= s[i]) && (s[i] <= 'f'))) {
   *val <<= 4;
   *val += s[i] - 'a' + 10;
  } else {
   done = 1;
  }
  if ((!done ? 1 : 0)) i++;
  if (i >= 9) done = 1;
 }
 return(i);
}