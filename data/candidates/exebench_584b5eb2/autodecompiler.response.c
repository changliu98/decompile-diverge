char *substitute(char *s, char old, char new)
{
 char *p = s;
 if(p)
 {
  while(*p != '\0')
  {
   if(*p == old)
   {
    *p = new;
    break;
   }
   p++;
  }
 }
 return s;
}