void __cdecl uppercase(int *chptr)
{
  int ch_0; // [rsp+0h] [rbp-Ch]

  ch_0 = *chptr;
  if ( *chptr >= 97 && ch_0 <= 105 || ch_0 >= 106 && ch_0 <= 114 || ch_0 >= 115 && ch_0 <= 122 )
    *chptr = ch_0 - 32;
}