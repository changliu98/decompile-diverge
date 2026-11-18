int func0(int a[], int len1, int b[], int len2)
{
 int hash[1000];
 memset(hash, 0, sizeof(hash));
 int i;
 for(i = 0; ; i++)
 {
  if(i >= len1)
   break;
  hash[a[i]] = 1;
 }
 char flag = 0;
 for(i = 0; ; i++)
 {
  if(i >= len2)
   break;
  if(hash[b[i]])
  {
   flag = 1;
   break;
  }
 }
 return !flag;
}