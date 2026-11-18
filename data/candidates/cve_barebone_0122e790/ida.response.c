char *__cdecl parse_content_length(char *buffer, char *end, int *length)
{
  char *v3; // rax
  char *v4; // rax
  bool v6; // [rsp+1h] [rbp-3Dh]
  bool v7; // [rsp+2h] [rbp-3Ch]
  char v8; // [rsp+3h] [rbp-3Bh]
  char v9; // [rsp+4h] [rbp-3Ah]
  bool v10; // [rsp+5h] [rbp-39h]
  bool v11; // [rsp+6h] [rbp-38h]
  bool v12; // [rsp+7h] [rbp-37h]
  char v13; // [rsp+8h] [rbp-36h]
  char v14; // [rsp+9h] [rbp-35h]
  int size; // [rsp+Ah] [rbp-34h]
  char *pa; // [rsp+Eh] [rbp-30h]
  int number; // [rsp+1Ah] [rbp-24h]

  while ( 1 )
  {
    v14 = 0;
    if ( buffer < end )
    {
      v13 = 1;
      if ( *buffer != 32 )
      {
        v13 = 1;
        if ( *buffer != 9 )
        {
          if ( *buffer != 13 || (v13 = 1, buffer[1] != 10) )
          {
            v12 = 0;
            if ( *buffer == 10 )
            {
              v11 = 1;
              if ( buffer[1] != 32 )
                v11 = buffer[1] == 9;
              v12 = v11;
            }
            v13 = v12;
          }
        }
      }
      v14 = v13;
    }
    if ( (v14 & 1) == 0 )
      break;
    ++buffer;
  }
  if ( buffer == end )
    return 0LL;
  size = 0;
  number = 0;
  while ( 1 )
  {
    v10 = 0;
    if ( buffer < end )
    {
      v10 = 0;
      if ( *buffer >= 48 )
        v10 = *buffer <= 57;
    }
    if ( !v10 )
      break;
    number = *buffer + 10 * number - 48;
    if ( number < 0 )
      return 0LL;
    ++size;
    ++buffer;
  }
  if ( buffer == end || !size )
    return 0LL;
  while ( 1 )
  {
    v9 = 0;
    if ( buffer < end )
    {
      v8 = 1;
      if ( *buffer != 32 )
      {
        v8 = 1;
        if ( *buffer != 9 )
        {
          v7 = 0;
          if ( *buffer == 10 )
          {
            v6 = 1;
            if ( buffer[1] != 32 )
              v6 = buffer[1] == 9;
            v7 = v6;
          }
          v8 = v7;
        }
      }
      v9 = v8;
    }
    if ( (v9 & 1) == 0 )
      break;
    ++buffer;
  }
  if ( buffer == end )
    return 0LL;
  v3 = buffer;
  pa = buffer + 1;
  if ( *v3 != 10 )
  {
    if ( *(pa - 1) != 13 )
      return 0LL;
    v4 = pa++;
    if ( *v4 != 10 )
      return 0LL;
  }
  *length = number;
  return pa;
}