int func0(char *str)
{
 char *token;
 int flag;

 token = strtok(str, " ");
 if (token != NULL)
 {
  if (strlen(token) % 2 != 0)
   flag = 1;
  else
   flag = 0;
 }
 else
  flag = 0;

 return flag;
}