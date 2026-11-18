void __cdecl func0(const char *text, char *out)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int i; // [rsp+14h] [rbp-1Ch]
  int j; // [rsp+18h] [rbp-18h]
  int space_len; // [rsp+1Ch] [rbp-14h]

  space_len = 0;
  j = 0;
  for ( i = 0; i < strlen(text); ++i )
  {
    if ( text[i] == 32 )
    {
      ++space_len;
    }
    else
    {
      if ( space_len == 1 )
      {
        v2 = j++;
        out[v2] = 95;
      }
      if ( space_len == 2 )
      {
        out[j] = 95;
        v3 = j + 1;
        j += 2;
        out[v3] = 95;
      }
      if ( space_len > 2 )
      {
        v4 = j++;
        out[v4] = 45;
      }
      space_len = 0;
      v5 = j++;
      out[v5] = text[i];
    }
  }
  if ( space_len == 1 )
  {
    v6 = j++;
    out[v6] = 95;
  }
  if ( space_len == 2 )
  {
    out[j] = 95;
    v7 = j + 1;
    j += 2;
    out[v7] = 95;
  }
  if ( space_len > 2 )
  {
    v8 = j++;
    out[v8] = 45;
  }
  out[j] = 0;
}