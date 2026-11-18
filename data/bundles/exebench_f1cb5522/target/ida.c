void __cdecl argorder(int ix1, int ix2, int *ox1, int *ox2)
{
  int ix2a; // [rsp+14h] [rbp-8h]
  int ix1a; // [rsp+18h] [rbp-4h]

  ix1a = ix1;
  ix2a = ix2;
  if ( ix1 > ix2 )
  {
    ix1a = ix2;
    ix2a = ix1;
  }
  *ox1 = ix1a;
  *ox2 = ix2a;
}