int func0(int *arr,int size)
{
 int i,sum=0;
 for(i=0;;i++)
 {
  if(i>=size) break;
  sum+=arr[i];
 }
 return sum;
}