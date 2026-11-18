int str_replace(char *s,char oldchar,char newchar)
{
 char *p = NULL;
 p = s;

 while(1)
 {
  p = strchr(p,oldchar);
  if(p == NULL) break;
  else *(p++) = newchar;
 }
 return 1;
}