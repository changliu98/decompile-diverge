char *strtoupper(char *str)
{
 int it;
 int len;
 int c;

 len = 8;
 it = 0;
 while (it < len)
 {
  if (str[it] >= 'a' && str[it] <= 'z')
   c = str[it] + ('A' - 'a');
  else
   c = str[it];
  str[it] = c;
  it++;
 }
 return (str);
}