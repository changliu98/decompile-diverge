char *__cdecl func0(const char *s)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // eax
  int j_0; // [rsp+4h] [rbp-6Ch]
  char temp; // [rsp+Bh] [rbp-65h]
  int k; // [rsp+Ch] [rbp-64h]
  int j; // [rsp+10h] [rbp-60h]
  int i; // [rsp+14h] [rbp-5Ch]
  int current_index; // [rsp+18h] [rbp-58h]
  int out_index; // [rsp+1Ch] [rbp-54h]
  char current[51]; // [rsp+20h] [rbp-50h]
  char *out; // [rsp+58h] [rbp-18h]
  int len; // [rsp+64h] [rbp-Ch]
  const char *sa; // [rsp+68h] [rbp-8h]

  sa = s;
  len = strlen(s);
  out = (char *)malloc(len + 2);
  out_index = 0;
  current_index = 0;
  for ( i = 0; i <= len; ++i )
  {
    if ( sa[i] != 32 && sa[i] )
    {
      v3 = current_index++;
      current[v3] = sa[i];
    }
    else
    {
      for ( j = 0; j < current_index - 1; ++j )
      {
        for ( k = j + 1; k < current_index; ++k )
        {
          if ( current[j] > current[k] )
          {
            temp = current[j];
            current[j] = current[k];
            current[k] = temp;
          }
        }
      }
      if ( out_index > 0 )
      {
        v1 = out_index++;
        out[v1] = 32;
      }
      for ( j_0 = 0; j_0 < current_index; ++j_0 )
      {
        v2 = out_index++;
        out[v2] = current[j_0];
      }
      current_index = 0;
    }
  }
  out[out_index] = 0;
  return out;
}