int ok_cp1251(const char *s,int n)
{
 int i;
 for(i=1;i<n;i++)
  if((unsigned char)s[i]==0x98)
   return 0;
 return 1;
}