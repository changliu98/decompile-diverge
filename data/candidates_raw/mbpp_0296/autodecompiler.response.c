int getInverCount(int *a,int size)
{
 int invCount = 0;
 int i,j;

 for(i = 0 ; i < size ; ++i)
 {
  for(j = i + 1 ; j < size ; ++j)
  {
   if(a[i] > a[j])
   {
    invCount++;
   }
  }
 }

 return invCount;
}