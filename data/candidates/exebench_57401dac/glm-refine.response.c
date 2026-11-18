void __cdecl std::swap<int>(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}