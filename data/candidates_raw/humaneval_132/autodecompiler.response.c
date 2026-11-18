int check_brackets(char *str)
{
 int i;
 int max_nesting_level;
 int current_nesting_level;
 int result;

 current_nesting_level = 0;
 max_nesting_level = 0;
 i = 0;
 while (1)
 {
  if (i >= strlen(str))
  {
   result = 0;
   break;
  }
  if (str[i] == '[')
   current_nesting_level++;
  if (str[i] == ']')
   current_nesting_level--;
  if (current_nesting_level < 0)
   current_nesting_level = 0;
  if (current_nesting_level > max_nesting_level)
   max_nesting_level = current_nesting_level;
  if (current_nesting_level <= max_nesting_level - 3)
  {
   result = 1;
   break;
  }
  i++;
 }
 return (result);
}