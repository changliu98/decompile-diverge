void findMinN(int *arr, int size, int k, int *output)
{
 int i;
 buildHeap(arr, size);
 if(k < arr[0])
  return ;
 else
 {
  arr[0] = k;
  heapify(arr, size, 0);
  for(i = 0 ; i < size ; i++)
   output[i] = arr[i];
 }
}