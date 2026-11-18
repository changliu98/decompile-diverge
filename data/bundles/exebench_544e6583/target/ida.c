void __cdecl SWAP(int *a, int *b)
{
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}