utf8proc_ssize_t __cdecl utf8proc_iterate(const utf8proc_uint8_t *str, utf8proc_ssize_t strlen, utf8proc_int32_t *dst)
{
  utf8proc_ssize_t v4; // [rsp+0h] [rbp-40h]
  const utf8proc_uint8_t *end; // [rsp+10h] [rbp-30h]
  unsigned int uc; // [rsp+1Ch] [rbp-24h]
  int uca; // [rsp+1Ch] [rbp-24h]
  const utf8proc_uint8_t *stra; // [rsp+30h] [rbp-10h]

  *dst = -1;
  if ( !strlen )
    return 0LL;
  if ( strlen >= 0 )
    v4 = strlen;
  else
    v4 = 4LL;
  end = &str[v4];
  stra = str + 1;
  uc = *str;
  if ( uc >= 0x80 )
  {
    if ( uc - 194 <= 0x32 )
    {
      if ( *str >= 0xE0u )
      {
        if ( *str >= 0xF0u )
        {
          if ( str + 3 < end && (*stra & 0xC0) == 128 && (str[2] & 0xC0) == 128 && (str[3] & 0xC0) == 128 )
          {
            if ( uc == 240 )
            {
              if ( *stra < 0x90u )
                return -3LL;
            }
            else if ( uc == 244 && *stra > 0x8Fu )
            {
              return -3LL;
            }
            *dst = str[3] & 0x3F | ((str[2] & 0x3F) << 6) | ((str[1] & 0x3F) << 12) | ((uc & 7) << 18);
            return 4LL;
          }
          return -3LL;
        }
        else if ( str + 2 < end && (*stra & 0xC0) == 128 && (str[2] & 0xC0) == 128 )
        {
          if ( uc == 237 && *stra > 0x9Fu )
          {
            return -3LL;
          }
          else
          {
            uca = str[2] & 0x3F | ((str[1] & 0x3F) << 6) | ((uc & 0xF) << 12);
            if ( uca >= 2048 )
            {
              *dst = uca;
              return 3LL;
            }
            else
            {
              return -3LL;
            }
          }
        }
        else
        {
          return -3LL;
        }
      }
      else if ( stra < end && (*stra & 0xC0) == 128 )
      {
        *dst = *stra & 0x3F | ((uc & 0x1F) << 6);
        return 2LL;
      }
      else
      {
        return -3LL;
      }
    }
    else
    {
      return -3LL;
    }
  }
  else
  {
    *dst = uc;
    return 1LL;
  }
}