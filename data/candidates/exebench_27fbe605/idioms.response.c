int vpf_str_to_num(char *str, int *res)
{
  int i = 0;
  char *c = str;
  while(*str)
  {
    int is_digit = ( *c >= '0' && *c <= '9');
    if(!is_digit)
      break;
    i = i * 10 + *c - '0';
    c++;
  }
  *res = i;
  return c - str;
}