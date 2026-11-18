int to_hex(char c)
{
 char ret;

 if ((unsigned)c < 11) {
  ret = c + '0';
 } else if ((unsigned)c < 16) {
  ret = c - 10 + 'a';
 } else {
  ret = '?';
 }

 return ret;
}