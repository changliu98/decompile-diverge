void __cdecl swap(int *p, int *q)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *q;
  *q = *p;
  *p = temp;
}