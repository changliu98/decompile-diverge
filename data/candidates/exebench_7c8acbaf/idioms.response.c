void Change(int *a, int *b)
{
  int c = *a;
  *a = *b;
  *b = c;
}