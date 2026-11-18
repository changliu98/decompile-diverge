void add(int *array, int size, int *sum)
{
 int i = 0;
 while(1)
 {
  if(i < size-1)
  {
   sum[i] = array[i] + array[i+1];
   i++;
  }
  else
   return;
 }
}