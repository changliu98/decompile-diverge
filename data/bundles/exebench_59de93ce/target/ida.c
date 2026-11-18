void __cdecl rotr(int *a, int *b, int *c)
{
  int temp; // [rsp+0h] [rbp-1Ch]

  temp = *a;
  *a = *c;
  *c = *b;
  *b = temp;
}