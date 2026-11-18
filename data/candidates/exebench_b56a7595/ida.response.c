void __cdecl rotr(int *a, int *b, int *c)
{
  int num; // [rsp+0h] [rbp-1Ch]

  num = *c;
  *c = *b;
  *b = *a;
  *a = num;
}