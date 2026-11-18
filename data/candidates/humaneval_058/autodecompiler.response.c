int *func0(int *array1, int array1Size, int *array2, int array2Size, int *outputSize)
{
 int *output = (int *)malloc(array1Size * sizeof(int));
 int k = 0;
 int i, j;
 for(i = 0; i < array1Size; i++)
 {
  int exists_in_out = 0;
  for(j = 0; j < k; j++)
   if(output[j] == array1[i])
   {
    exists_in_out = 1;
    break;
   }
  if(!exists_in_out)
  {
   for(j = 0; j < array2Size; j++)
    if(array1[i] == array2[j])
     output[k++] = array1[i];
  }
 }

 for(i = 0; i < k-1; i++)
  for(j = 0; j < k-i-1; j++)
   if(output[j] > output[j+1])
   {
    int temp = output[j];
    output[j] = output[j+1];
    output[j+1] = temp;
   }

 *outputSize = k;
 return output;
}