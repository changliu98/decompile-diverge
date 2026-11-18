int oddSum(int * arr, int n)
{
 int i,sum=0;
 for(i=0; ; i++)
 {
  if(2*i<n)
  {
   if(arr[2*i]%2==1)
   sum+=arr[2*i];
  }
  else break;
 }
 return sum;
}