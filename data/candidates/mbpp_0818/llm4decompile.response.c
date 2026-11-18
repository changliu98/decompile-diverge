int func0(char *str)
{
 int i;
 int ctr = 0;

 for (i = 0; i < strlen(str); i++) {
  if (str[i] >= 'a' && str[i] <= 'z')
   ctr++;
 }

 return ctr;
}