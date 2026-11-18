static int parse_width(const char *str, int *len_p)
{
 int val = 0, len;
 for(len=0; str[len]!='\0'; len++) {
  if(str[len] < '0' || str[len] > '9') break;
  int digit = str[len] - '0';
  val = val * 10 + digit;
 }
 *len_p = len;
 return val;
}