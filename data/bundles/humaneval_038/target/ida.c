void __cdecl func0(char *s, int encode)
{
  int v2; // [rsp+8h] [rbp-28h]
  char temp_0; // [rsp+Eh] [rbp-22h]
  char temp; // [rsp+Fh] [rbp-21h]
  int i; // [rsp+14h] [rbp-1Ch]
  char x[4]; // [rsp+18h] [rbp-18h] BYREF
  int num; // [rsp+1Ch] [rbp-14h]
  int l; // [rsp+20h] [rbp-10h]
  int encodea; // [rsp+24h] [rbp-Ch]
  char *sa; // [rsp+28h] [rbp-8h]

  sa = s;
  encodea = encode;
  l = strlen(s);
  num = (l + 2) / 3;
  for ( i = 0; i < num; ++i )
  {
    if ( 3 * i + 3 > l )
      v2 = l - 3 * i;
    else
      v2 = 3;
    strncpy(x, &sa[3 * i], v2);
    x[v2] = 0;
    if ( v2 == 3 )
    {
      if ( encodea )
      {
        temp = x[2];
        x[2] = x[1];
        x[1] = x[0];
        x[0] = temp;
      }
      else
      {
        temp_0 = x[0];
        x[0] = x[1];
        x[1] = x[2];
        x[2] = temp_0;
      }
    }
    strncpy(&sa[3 * i], x, v2);
  }
}