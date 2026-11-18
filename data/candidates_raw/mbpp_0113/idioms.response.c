int is_number(char *text)
{
 char *t = text;
 int len = strlen(text);
 int i;
 while(*t == ' ')
 {
  t++;
  len--;
 }
 if(len < 1)
  return -1;
 if(*t == '+' || *t == '-')
 {
  for(i = 1; i < len; i++)
  {
   if((*(t + i) < '0') || (*(t + i) > '9'))
    return 0;
  }
  return 1;
 }
 for(i = 0; i < len; i++)
 {
  if((*(t + i) < '0') || (*(t + i) > '9'))
   return 0;
 }
 return 1;
}