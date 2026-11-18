int c_insensitive(char *a, char *b)
{
 int x=0;

 while(a[x] != '\0')
 {
  if(a[x] >96 && a[x] < 123)
   a[x] -= 'a' - 'A';
  x++;
 }

 x =0;
 while(b[x] != '\0')
 {
  if(b[x] >96 && b[x] < 123)
   b[x] -= 'a' - 'A';
  x++;
 }



 for(x=0; a[x] != '\0' && b[x] != '\0'; x++)
 {
  if(a[x] > b[x])
  return 1;
  else if(a[x] < b[x])
   return -1;
  else
   continue;
 }

 return 0;
}