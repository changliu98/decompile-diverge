void __cdecl std::swap<int>(int *a, int *b)
{
  int c = *a;
  *a = *b;
  *b = c;
}