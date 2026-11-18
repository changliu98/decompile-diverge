void __cdecl swap_long(long *pi)
{
  unsigned __int8 t; // [rsp+Fh] [rbp-9h]
  unsigned __int8 ta; // [rsp+Fh] [rbp-9h]

  t = *(_BYTE *)pi;
  *(_BYTE *)pi = *((_BYTE *)pi + 3);
  *((_BYTE *)pi + 3) = t;
  ta = *((_BYTE *)pi + 1);
  *((_BYTE *)pi + 1) = *((_BYTE *)pi + 2);
  *((_BYTE *)pi + 2) = ta;
}