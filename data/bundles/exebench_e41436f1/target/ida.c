void __cdecl htond(double *x)
{
  int Holding_Buffer; // [rsp+Ch] [rbp-14h]

  Holding_Buffer = *(_DWORD *)x;
  *(_DWORD *)x = htonl(*((_DWORD *)x + 1));
  *((_DWORD *)x + 1) = htonl(Holding_Buffer);
}