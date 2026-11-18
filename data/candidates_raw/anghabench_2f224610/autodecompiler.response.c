int search(int *a,int size,int num)
{
 int i=0;
 int flag;
 while(1)
 {
  if(i<size)
  {
   if(a[i]==num)
   {
    flag = 1;
    break;
   }
   else
   {
    i++;
    continue;
   }
  }
  else
  {
   flag = 0;
   break;
  }
 }

 return flag;
}