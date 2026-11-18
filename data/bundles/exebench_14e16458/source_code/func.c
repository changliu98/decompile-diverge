
void int_to_str(unsigned int n, char *str)
{
  int i;

  for (i = 9; i >= 0; i--) {
    str[i] = n%10 + 48;
    n /= 10;
  }
  str[10] = '\0';
# 19 "str.c"
}
