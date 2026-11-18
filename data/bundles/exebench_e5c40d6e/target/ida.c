void __cdecl swap(int *a, int *b)
{
  int v2; // ecx
  int v3; // ecx

  v2 = *a ^ *b;
  *a = v2;
  v3 = *b ^ v2;
  *b = v3;
  *a ^= v3;
}