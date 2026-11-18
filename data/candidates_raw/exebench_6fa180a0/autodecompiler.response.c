void bubbleSort(int *a)
{
 int i,j,temp;
 do
 {
  j=1;
  for(i=1;i<=3;i++)
  {
   if(a[i-1]>a[i])
   {
    temp=a[i];
    a[i]=a[i-1];
    a[i-1]=temp;
    j=0;
   }
  }
 }while(!j);
}