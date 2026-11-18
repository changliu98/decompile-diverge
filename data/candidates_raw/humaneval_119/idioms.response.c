char *isBalanced(char *str1, char *str2)
{
 int count = 0;
 int len1 = strlen(str1);
 int len2 = strlen(str2);
 int can = 1;
 for (int i = 0; i < len1; i++)
 {
  if (str1[i] == '(')
   count++;
  if (str1[i] == ')')
   count--;
  if (count < 0)
   can = 0;
 }
 for (int i = 0; i < len2; i++)
 {
  if (str2[i] == '(')
   count++;
  if (str2[i] == ')')
   count--;
  if (count < 0)
   can = 0;
 }
 if (count == 0 && can == 1)
  return "true";
 else
 {
  count = 0;
  can = 1;
  for (int i = 0; i < len2; i++)
  {
   if (str2[i] == '(')
    count++;
   if (str2[i] == ')')
    count--;
   if (count < 0)
    can = 0;
  }
  for (int i = 0; i < len1; i++)
  {
   if (str1[i] == '(')
    count++;
   if (str1[i] == ')')
    count--;
   if (count < 0)
    can = 0;
  }
  if (count == 0 && can == 1)
   return "true";
  else
   return "false";
 }
}