int str_to_int(char *str, int *num)
{
 int i;
 int base;
 int digit;

 i = 0;
 base = 10;
 *num = 0;
 if (str[0] == '0' && str[1] == 'x') {
  i = 2;
  base = 16;
 }
 if (str[i] == '\0') {
  return -1;
 }
 while (str[i] != '\0') {
  if (str[i] >= '0' && str[i] <= '9') {
   digit = str[i] - '0';
  } else if (base == 16 && str[i] >= 'a' && str[i] <= 'f') {
   digit = str[i] - 'a' + 10;
  } else if (base == 16 && str[i] >= 'A' && str[i] <= 'F') {
   digit = str[i] - 'A' + 10;
  } else {
   return -1;
  }
  *num = *num * base + digit;
  i++;
 }
 return 0;
}