void __cdecl si_swapl(int *d)
{
  int u; // [rsp+2h] [rbp-10h]

  LOBYTE(u) = HIBYTE(*d);
  HIBYTE(u) = *d;
  BYTE1(u) = BYTE2(*d);
  BYTE2(u) = BYTE1(*d);
  *d = u;
}