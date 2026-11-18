int quicksort_partition_harness(double array[])
{
  int left, right, pivot_index, pivot_new_index;

  pivot_index = 0;
  left = 1;
  right = 2;

  if(array[left] > array[right])
  {
    swap(array, left, right);
    pivot_index = 1;
  }
  else
    pivot_index = 0;

  right = 3;

  if(array[pivot_index] > array[right])
  {
    swap(array, pivot_index, right);
    pivot_new_index = pivot_index;
  }
  else
    pivot_new_index = pivot_index;

  if(array[left] > array[right])
  {
    swap(array, left, right);
    if(pivot_new_index == 0)
      pivot_new_index = 4;
  }
  else
    pivot_new_index = pivot_new_index;

  if(array[pivot_new_index] > array[left])
  {
    swap(array, pivot_new_index, left);
    if(pivot_new_index == 4)
      pivot_new_index = 2;
    if(pivot_new_index == 5)
      pivot_new_index = 1;
  }
  else
  {
    if(pivot_new_index == 4)
      pivot_new_index = 1;
    if(pivot_new_index == 5)
      pivot_new_index = 2;
  }

  return pivot_new_index;
}