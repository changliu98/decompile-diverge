void __cdecl int_swap(int *a, int *b)
{
  int c; // [rsp+8h] [rbp-18h]

  c = *a;
  *a = *b;
  *b = c;
}