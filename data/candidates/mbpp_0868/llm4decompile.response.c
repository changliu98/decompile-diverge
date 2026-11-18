int func0(char *a)
{
 int i, c;

 c = 0;
 while(*a == ' ')
  a++;
 for(i = 0; i < strlen(a); i++)
 {
  if(a[i] != ' ')
   c++;
  else
   c = 0;
 }
 return c;
}