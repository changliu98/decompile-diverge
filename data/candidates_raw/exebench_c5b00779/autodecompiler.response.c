int fibsearch(int *a,int n,int key)
{
 int f[13]={0,1,2,3,5,8,13,21,34,55,89,144,233};
 int k=0,i,m;
 int low=1;
 int high=n;
 int mid;
 while(n>f[k]-1)
  k++;
 for(i=n;i<f[k]-1;i++)
  a[i]=a[n];
 do
 {
  if(low<=high)
  {
   mid=low+f[k-1]-1;
   if(key<a[mid])
   {
    high=mid-1;
    k=k-1;
   }
   else if(key>a[mid])
   {
    low=mid+1;
    k=k-2;
   }
   else
   {
    if(mid<n)
     m=mid;
    else
     m=n;
    return m;
   }
  }
  else
   return 0;
 }while(1);
}