void swap(int *a, int *b)
{
  int temp;
  if (a != ((void *)0) && b != ((void *)0))
  {
    temp = *a;
    *a = *b;
    *b = temp;
  }
}