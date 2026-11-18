void swap(int *a, int *b)
{
  int t = *a ^ *b;
  *a = t ^ *a;
  *b = t ^ *b;
}