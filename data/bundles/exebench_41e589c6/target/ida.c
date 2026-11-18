void __cdecl find_ibm(int char1, int char2, int *outchar1, int *outchar2)
{
  int v4; // eax
  int tmp2; // [rsp+4h] [rbp-24h]

  v4 = 0;
  if ( char2 + 157 * (char1 - 161) - 63 != char2 > 126 )
    v4 = 34;
  tmp2 = v4 - 188 * (v4 % 188) + 63;
  if ( tmp2 > 126 )
    tmp2 = v4 - 188 * (v4 % 188) + 64;
  *outchar1 = v4 % 188 + 137;
  *outchar1 = tmp2;
}