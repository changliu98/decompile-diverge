char *__cdecl func0(const char *str, char ch_0)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  char *new_str; // [rsp+8h] [rbp-48h]
  int i_2; // [rsp+10h] [rbp-40h]
  int i_1; // [rsp+14h] [rbp-3Ch]
  int i_0; // [rsp+18h] [rbp-38h]
  int new_index; // [rsp+1Ch] [rbp-34h]
  char *new_str_0; // [rsp+20h] [rbp-30h]
  int i; // [rsp+2Ch] [rbp-24h]
  int last; // [rsp+30h] [rbp-20h]
  int first; // [rsp+34h] [rbp-1Ch]
  int len; // [rsp+38h] [rbp-18h]

  len = strlen(str);
  first = -1;
  last = -1;
  for ( i = 0; i < len; ++i )
  {
    if ( str[i] == ch_0 )
    {
      if ( first == -1 )
        first = i;
      last = i;
    }
  }
  if ( first == -1 || last == -1 || first == last )
  {
    new_str = (char *)malloc(len + 1);
    strcpy(new_str, str);
    return new_str;
  }
  else
  {
    new_str_0 = (char *)malloc(len - 2 + 1);
    new_index = 0;
    for ( i_0 = 0; i_0 < first; ++i_0 )
    {
      v2 = new_index++;
      new_str_0[v2] = str[i_0];
    }
    for ( i_1 = first + 1; i_1 < last; ++i_1 )
    {
      v3 = new_index++;
      new_str_0[v3] = str[i_1];
    }
    for ( i_2 = last + 1; i_2 < len; ++i_2 )
    {
      v4 = new_index++;
      new_str_0[v4] = str[i_2];
    }
    new_str_0[new_index] = 0;
    return new_str_0;
  }
}