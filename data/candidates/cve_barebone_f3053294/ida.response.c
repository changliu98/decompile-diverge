char *__cdecl utf_16le_to_utf_8_truncated(const wchar_t *utf_16, char *utf_8, size_t utf_8_len)
{
  const wchar_t *v3; // rax
  char *v4; // rax
  _BYTE *v5; // rax
  _BYTE *v6; // rax
  _BYTE *v7; // rax
  uint32_t uc; // [rsp+0h] [rbp-2Ch]
  wchar_t c2; // [rsp+4h] [rbp-28h]
  wchar_t c; // [rsp+8h] [rbp-24h]
  size_t utf_8_lena; // [rsp+Ch] [rbp-20h]
  char *utf_8a; // [rsp+14h] [rbp-18h]

  utf_8a = utf_8;
  utf_8_lena = utf_8_len;
  if ( !utf_8_len )
    return utf_8;
  while ( 1 )
  {
    v3 = utf_16++;
    c = *v3;
    if ( !*v3 )
      break;
    if ( c < 55296 || c >= 56320 )
    {
      if ( c < 56320 || c >= 57344 )
        uc = *v3;
      else
        uc = 65533;
    }
    else
    {
      c2 = *utf_16;
      if ( *utf_16 )
      {
        ++utf_16;
        if ( c2 < 56320 || c2 >= 57344 )
          uc = 65533;
        else
          uc = ((c2 - 56320) | ((c - 55296) << 10)) + 0x10000;
      }
      else
      {
        uc = 65533;
      }
    }
    if ( uc >= 0x80 )
    {
      if ( uc >= 0x800 )
      {
        if ( uc >= 0x10000 )
        {
          if ( utf_8_lena < 5 )
            break;
          *utf_8a = (uc >> 18) & 3 | 0xF0;
          utf_8a[1] = (uc >> 12) & 0x3F | 0x80;
          utf_8a[2] = (uc >> 6) & 0x3F | 0x80;
          v7 = utf_8a + 3;
          utf_8a += 4;
          *v7 = uc & 0x3F | 0x80;
          utf_8_lena -= 3LL;
        }
        else
        {
          if ( utf_8_lena < 4 )
            break;
          *utf_8a = (uc >> 12) & 0xF | 0xE0;
          utf_8a[1] = (uc >> 6) & 0x3F | 0x80;
          v6 = utf_8a + 2;
          utf_8a += 3;
          *v6 = uc & 0x3F | 0x80;
          utf_8_lena -= 3LL;
        }
      }
      else
      {
        if ( utf_8_lena < 3 )
          break;
        *utf_8a = (uc >> 6) & 0x3F | 0xC0;
        v5 = utf_8a + 1;
        utf_8a += 2;
        *v5 = uc & 0x3F | 0x80;
        utf_8_lena -= 2LL;
      }
    }
    else
    {
      if ( utf_8_lena < 2 )
        break;
      v4 = utf_8a++;
      *v4 = uc;
      --utf_8_lena;
    }
  }
  *utf_8a = 0;
  return utf_8a;
}