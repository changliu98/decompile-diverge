void my_add(int a, int *b)
{
  if (b != ((void *)0))
    *b += a;
}