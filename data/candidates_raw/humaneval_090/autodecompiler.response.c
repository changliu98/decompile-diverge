int findSecondMinimum(int *a,int n)
{
 int i,min1,min2;
 if(n<3)
 {
  return -1;
 }
 min1=min2=INT_MAX;
 for(i=0;i<n;i++)
 {
  if(a[i]<min1)
  {
   min2=min1;
   min1=a[i];
  }
  else if(a[i]<min2 && a[i]!=min1)
  {
   min2=a[i];
  }
 }
 if(min2==INT_MAX)
 {
  return -1;
 }
 return min2;
}