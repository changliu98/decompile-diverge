void bucket_sort(int *list, int l_size)
{
 int max = 0, i, j, k, *bucket;

 for(i = 0; i < l_size; i++)
 {
  if(list[i] > max)
   max = list[i];
 }

 bucket = (int *)malloc(sizeof(int) * (max + 1));

 for(j = 0; j <= max; j++)
  bucket[j] = 0;

 for(i = 0; i < l_size; i++)
  bucket[list[i]]++;

 for(j = 0, k = 0; j <= max; j++)
  for(i = 0; i < bucket[j]; i++)
   list[k++] = j;

 free(bucket);
}