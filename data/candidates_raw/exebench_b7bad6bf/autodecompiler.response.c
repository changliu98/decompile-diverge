int swap(int *a, int *b)
{
   int t = *a;
   *a = *b;
   *b = t;
   return 0;
}