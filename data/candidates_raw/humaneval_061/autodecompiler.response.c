int check_brackets(char *str)
{
 int i;
 int level;
 char ok;

 level = 0;
 i = 0;
 while (1)
 {
  if (i >= strlen(str))
  {
   ok = (level == 0);
   break;
  }
  if (str[i] == '(') level++;
  if (str[i] == ')') level--;
  if (level < 0)
  {
   ok = 0;
   break;
  }
  i++;
 }
 return (ok & 1);
}