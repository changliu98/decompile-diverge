MOBI_RET __cdecl mobi_search_links_kf7(
        MOBIResult *result,
        const unsigned __int8 *data_start,
        const unsigned __int8 *data_end)
{
  char *v3; // rax
  int v4; // ecx
  bool v6; // [rsp+Eh] [rbp-62h]
  bool v7; // [rsp+Fh] [rbp-61h]
  size_t v8; // [rsp+10h] [rbp-60h]
  int i; // [rsp+18h] [rbp-58h]
  unsigned __int8 last_border; // [rsp+1Dh] [rbp-53h]
  unsigned __int8 *data; // [rsp+20h] [rbp-50h]
  unsigned __int8 *dataa; // [rsp+20h] [rbp-50h]
  size_t needle2_length; // [rsp+30h] [rbp-40h]
  size_t needle1_length; // [rsp+38h] [rbp-38h]

  if ( !result )
    return 2;
  result->end = 0LL;
  result->start = 0LL;
  result->value[0] = 0;
  if ( !data_start || !data_end )
    return 2;
  needle1_length = strlen("filepos=");
  needle2_length = strlen("recindex=");
  if ( needle1_length <= needle2_length )
    v8 = needle2_length;
  else
    v8 = needle1_length;
  if ( &data_start[v8] > data_end )
    return 0;
  data = (unsigned __int8 *)data_start;
  last_border = 60;
  while ( 1 )
  {
    while ( 1 )
    {
      if ( data > data_end )
        return 0;
      if ( *data == 60 || *data == 62 )
        last_border = *data;
      if ( &data[v8] <= data_end
        && (!memcmp(data, "filepos=", needle1_length) || !memcmp(data, "recindex=", needle2_length)) )
      {
        break;
      }
      ++data;
    }
    if ( last_border == 60 )
      break;
    data += v8;
  }
  while ( 1 )
  {
    v7 = 0;
    if ( data >= data_start )
    {
      v7 = 0;
      if ( ((*__ctype_b_loc())[*data] & 0x2000) == 0 )
        v7 = *data != 60;
    }
    if ( !v7 )
      break;
    --data;
  }
  dataa = data + 1;
  result->start = dataa;
  for ( i = 0; ; ++i )
  {
    v6 = 0;
    if ( dataa <= data_end )
    {
      v6 = 0;
      if ( ((*__ctype_b_loc())[*dataa] & 0x2000) == 0 )
      {
        v6 = 0;
        if ( *dataa != 62 )
          v6 = i < 150;
      }
    }
    if ( !v6 )
      break;
    v3 = (char *)dataa++;
    v4 = i;
    result->value[v4] = *v3;
  }
  if ( *(dataa - 1) == 47 && *dataa == 62 )
  {
    --dataa;
    --i;
  }
  result->end = dataa;
  result->value[i] = 0;
  return 0;
}