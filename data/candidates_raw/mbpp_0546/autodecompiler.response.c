int last(char *str, char ch)
{
 int index;
 int length = strlen(str);
 int found = -1;

 for (index = 0; index < length; index++)
 {
  if (str[index] == ch)
  {
   found = index;
  }
 }

 int result;

 if (found == -1)
 {
  result = -1;
 }
 else
 {
  result = found + 1;
 }

 return result;
}