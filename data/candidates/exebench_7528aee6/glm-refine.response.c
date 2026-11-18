void __cdecl std::swap<int>(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}