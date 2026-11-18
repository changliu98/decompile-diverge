void __cdecl std::swap<int>(unsigned int *a, unsigned int *b)
{
  unsigned int temp = *a;
  *a = *b;
  *b = temp;
}