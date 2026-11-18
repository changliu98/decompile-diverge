int __cdecl get_char_utf8(unsigned int *x, const char *s)
{
  char f; // [rsp+0h] [rbp-30h]
  char e; // [rsp+4h] [rbp-2Ch]
  char d; // [rsp+8h] [rbp-28h]
  char c; // [rsp+Ch] [rbp-24h]
  char b; // [rsp+10h] [rbp-20h]
  int a; // [rsp+14h] [rbp-1Ch]

  a = *(unsigned __int8 *)s;
  if ( (a & 0x80) != 0 )
  {
    if ( (a & 0x40) != 0 )
    {
      b = s[1];
      if ( (b & 0xC0) == 128 )
      {
        if ( (a & 0x20) != 0 )
        {
          c = s[2];
          if ( (c & 0xC0) == 128 )
          {
            if ( (a & 0x10) != 0 )
            {
              d = s[3];
              if ( (d & 0xC0) == 128 )
              {
                if ( (a & 8) != 0 )
                {
                  e = s[4];
                  if ( (e & 0xC0) == 128 )
                  {
                    if ( (a & 4) != 0 )
                    {
                      f = s[5];
                      if ( (f & 0xC0) == 128 )
                      {
                        if ( (a & 2) != 0 )
                        {
                          *x = -1;
                          return -1;
                        }
                        else if ( (b & 0x3C | a & 1) > 0 )
                        {
                          *x = f & 0x3F | ((e & 0x3F) << 6) | ((d & 0x3F) << 12) | ((c & 0x3F) << 18) | ((b & 0x3F) << 24) | ((a & 1) << 30);
                          return 6;
                        }
                        else
                        {
                          *x = -1;
                          return -1;
                        }
                      }
                      else
                      {
                        *x = -1;
                        return -1;
                      }
                    }
                    else if ( (b & 0x38 | a & 3) > 0 )
                    {
                      *x = e & 0x3F | ((d & 0x3F) << 6) | ((c & 0x3F) << 12) | ((b & 0x3F) << 18) | ((a & 3) << 24);
                      return 5;
                    }
                    else
                    {
                      *x = -1;
                      return -1;
                    }
                  }
                  else
                  {
                    *x = -1;
                    return -1;
                  }
                }
                else if ( (b & 0x30 | a & 7) > 0 )
                {
                  *x = d & 0x3F | ((c & 0x3F) << 6) | ((b & 0x3F) << 12) | ((a & 7) << 18);
                  return 4;
                }
                else
                {
                  *x = -1;
                  return -1;
                }
              }
              else
              {
                *x = -1;
                return -1;
              }
            }
            else if ( (b & 0x20 | a & 0xF) > 0 )
            {
              *x = c & 0x3F | ((b & 0x3F) << 6) | ((a & 0xF) << 12);
              return 3;
            }
            else
            {
              *x = -1;
              return -1;
            }
          }
          else
          {
            *x = -1;
            return -1;
          }
        }
        else if ( (a & 0x1E) != 0 )
        {
          *x = b & 0x3F | ((a & 0x1F) << 6);
          return 2;
        }
        else
        {
          *x = -1;
          return -1;
        }
      }
      else
      {
        *x = -1;
        return -1;
      }
    }
    else
    {
      *x = -1;
      return -1;
    }
  }
  else
  {
    *x = a;
    return a != 0;
  }
}