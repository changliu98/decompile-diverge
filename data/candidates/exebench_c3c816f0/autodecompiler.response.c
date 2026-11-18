static int char2num(char c, char *i)
{
 int ret = 0;

 if ((c >= '0') && (c <= '9')) {
  *i = c - '0';
 } else if ((c >= 'A') && (c <= 'F')) {
  *i = c - 'A' + 10;
 } else if ((c >= 'a') && (c <= 'f')) {
  *i = c - 'a' + 10;
 } else {
  ret = -1;
 }

 return ret;
}