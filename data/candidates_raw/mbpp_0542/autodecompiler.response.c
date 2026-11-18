char *func0(char *str)
{
 int i;
 strcpy(func0_result, str);
 for (i = 0;; i++) {
  if (func0_result[i] == '\0')
   break;
  if (func0_result[i] == ' ' || func0_result[i] == ','
      || func0_result[i] == '.')
   func0_result[i] = ':';
 }
 return func0_result;
}