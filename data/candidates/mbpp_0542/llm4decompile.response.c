char *func0(char *text)
{
 int i;

 strcpy(func0::result, text);
 for (i = 0; func0::result[i] != '\0'; i++)
  if (func0::result[i] == ' ' || func0::result[i] == ',' || func0::result[i] == '.')
   func0::result[i] = ':';

 return func0::result;
}