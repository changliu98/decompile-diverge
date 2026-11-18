int prime(int n)
{
 int i, j, k, l = 0;
 for(i = 0; i < n; i++)
 {
  if(i <= 1)
   continue;
  else
  {
   int flag = 1;
   for(j = 2; j < i; j++)
   {
    if(i % j == 0)
    {
     flag = 0;
     break;
    }
   }
   if(flag)
    l++;
  }
 }
 return l;
}