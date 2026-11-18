void __cdecl swap(int *a, int *b)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *b;
  *b = *a;
  *a = temp;
}