int int2arr(int *arr,int num)
{
 int i=0;
 while(num)
 {
  arr[i]=num%10;
  i++;
  num=num/10;
 }
 return i;
}