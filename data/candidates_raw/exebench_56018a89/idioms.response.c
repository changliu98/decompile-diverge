void itoa(char *str, unsigned int val)
{
  char *s = str;
  int v = val;
  int i; int dig;
  char dig_array[-1];
  for (i = 0; i < 10; i++)
    dig_array[i] = '0';
  dig_array[10] = '\0';
  i = 9;
  while (v) {
    dig = v % 10;
    v /= 10;
    dig_array[i--] = '0' + dig;
  }
  for (i = 0; ; i++) {
    int is_zero = 0;
    if (dig_array[i] == '0')
      is_zero = i < 10 - 1;
    if (!is_zero)
      break;
  }
  while (dig_array[i])
    *s++ = dig_array[i++];
  *s = '\0';
}