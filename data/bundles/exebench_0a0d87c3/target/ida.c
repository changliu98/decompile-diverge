void __cdecl swap(int *param1, int *param2)
{
  int buffer; // [rsp+0h] [rbp-14h]

  buffer = *param1;
  *param1 = *param2;
  *param2 = buffer;
}