const char *__cdecl func0(int n, const char **test_list)
{
  int v2; // eax
  int i_0; // [rsp+0h] [rbp-80h]
  int index; // [rsp+4h] [rbp-7Ch]
  int max; // [rsp+8h] [rbp-78h]
  int j_0; // [rsp+Ch] [rbp-74h]
  int found_0; // [rsp+10h] [rbp-70h]
  int j; // [rsp+14h] [rbp-6Ch]
  int found; // [rsp+18h] [rbp-68h]
  int pos; // [rsp+1Ch] [rbp-64h]
  char word[50]; // [rsp+20h] [rbp-60h] BYREF
  const char *str; // [rsp+60h] [rbp-20h]
  int i; // [rsp+68h] [rbp-18h]
  int unique; // [rsp+6Ch] [rbp-14h]
  const char **test_lista; // [rsp+70h] [rbp-10h]
  int na; // [rsp+7Ch] [rbp-4h]

  na = n;
  test_lista = test_list;
  unique = 0;
  for ( i = 0; i < na; ++i )
  {
    str = test_lista[i];
    pos = 0;
    while ( *str )
    {
      if ( ((*__ctype_b_loc())[*str] & 0x2000) != 0 )
      {
        if ( pos > 0 )
        {
          word[pos] = 0;
          found = 0;
          for ( j = 0; j < unique; ++j )
          {
            if ( !strcmp((const char *)&func0_words + 56 * j, word) )
            {
              ++*((_DWORD *)&func0_words + 14 * j + 13);
              found = 1;
              break;
            }
          }
          if ( !found )
          {
            strcpy((char *)&func0_words + 56 * unique, word);
            *((_DWORD *)&func0_words + 14 * unique++ + 13) = 1;
          }
          pos = 0;
        }
      }
      else
      {
        v2 = pos++;
        word[v2] = *str;
      }
      ++str;
    }
    if ( pos > 0 )
    {
      word[pos] = 0;
      found_0 = 0;
      for ( j_0 = 0; j_0 < unique; ++j_0 )
      {
        if ( !strcmp((const char *)&func0_words + 56 * j_0, word) )
        {
          ++*((_DWORD *)&func0_words + 14 * j_0 + 13);
          found_0 = 1;
          break;
        }
      }
      if ( !found_0 )
      {
        strcpy((char *)&func0_words + 56 * unique, word);
        *((_DWORD *)&func0_words + 14 * unique++ + 13) = 1;
      }
    }
  }
  max = 0;
  index = 0;
  for ( i_0 = 0; i_0 < unique; ++i_0 )
  {
    if ( *((_DWORD *)&func0_words + 14 * i_0 + 13) > max )
    {
      max = *((_DWORD *)&func0_words + 14 * i_0 + 13);
      index = i_0;
    }
  }
  return (char *)&func0_words + 56 * index;
}