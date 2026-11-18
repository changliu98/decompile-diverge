void heapify(int *a,int n)
{
 int temp,i,j,k;
 for(i=n/2-1;i>=0;i--)
 {
  j=2*i+1;
  while(j<n)
  {
   if((j+1)<n && a[j]<a[j+1])
    j++;
   if(a[i]>a[j])
    break;
   else
   {
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
    i=j;
    j=2*j+1;
   }
  }
 }
}