void __cdecl set_mac(char *setto, char *from)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 6; ++i )
    setto[i] = from[i];
}