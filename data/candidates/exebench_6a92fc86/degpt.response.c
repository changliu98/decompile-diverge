int parse_width(char *str,int *len_p)

{
  int digit;
  int len;
  int val;
  int *len_p_local;
  char *str_local;
  
  val = 0;
  for (len = 0; ((str[len] != '\0' && ('/' < str[len])) && (str[len] < ':')); len = len + 1) {
    val = val * 10 + str[len] + -0x30;
  }
  *len_p = len;
  return val;
}