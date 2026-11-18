int func0(int *a,int n)
{
 int mid;
 int low=0,high=n-1;
 int x;
 while(low<=high)
 {
  mid=(low+high)/2;
  if((a[mid]!=mid+1)&&(a[mid-1]==mid))
  {
   x=mid+1;
   break;
  }
  else if(a[mid]!=(mid+1))
  {
   high=mid-1;
  }
  else
  {
   low=mid+1;
  }
 }
 return x;
}