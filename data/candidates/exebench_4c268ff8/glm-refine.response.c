void std::swap<int>(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}