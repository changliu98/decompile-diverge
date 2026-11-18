void mystrncpy(char *s, char *t, int n)
{
 if(n != 0)
 {
  int i = 0;
  while(1)
  {
   if(*t == '\0' || i >= n-1)
    break;
   else
   {
    *s++ = *t++;
    i++;
   }
  }
 }
 else
  *s = '\0';
}