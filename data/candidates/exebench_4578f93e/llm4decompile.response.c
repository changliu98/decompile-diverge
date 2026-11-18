char * mystrncpy(char *dest,char *src,int n)
{
 int i;
 char *p;
 for(i=0,p=dest;i<n && *src!='\0';i++)
  *p++ = *src++;
 *p = '\0';
 return dest;
}