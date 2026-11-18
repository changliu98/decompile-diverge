int func0(char *str)
{
 char *token;
 int result;

 token = strtok(str, " ");
 if (token != NULL)
 {
  if (strlen(token) % 2 == 0)
   result = 1;
  else
   result = 0;
 }
 else
  result = 0;
 return (result);
}