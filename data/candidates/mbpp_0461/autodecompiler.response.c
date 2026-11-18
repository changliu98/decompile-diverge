int func0(char *str)
{
 int counter;
 size_t i;
 int result;

 counter = 0;
 i = 0;
 while (i < strlen(str))
 {
  if ((int)str[i] >= 65 && (int)str[i] <= 90)
   counter++;
  result = counter;
  i++;
 }
 return (result);
}