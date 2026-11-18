int *func0(int min, int max)
{
 int range;
 int it;
 int *arr;

 range = max - min + 1;
 arr = (int *)malloc(sizeof(int) * range);
 arr[0] = range;
 it = 1;
 while (it < range)
 {
  arr[it] = arr[it - 1] + 2;
  it++;
 }
 return (arr);
}