int __cdecl u_get(int *up, char *s)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  if ( (unsigned __int8)*s >= 0x80u )
  {
    if ( (unsigned __int8)*s >= 0xC0u )
    {
      if ( (unsigned __int8)*s >= 0xE0u )
      {
        if ( (unsigned __int8)*s >= 0xF0u )
        {
          if ( (unsigned __int8)*s >= 0xF8u )
          {
            if ( (unsigned __int8)*s >= 0xFCu )
            {
              if ( (unsigned __int8)*s >= 0xFEu )
              {
                return 0;
              }
              else
              {
                *up = s[5] & 0x3F | ((s[4] & 0x3F | ((s[3] & 0x3F | ((s[2] & 0x3F | ((s[1] & 0x3F | ((*s & 1) << 6)) << 6)) << 6)) << 6)) << 6);
                v6 = 0;
                if ( (*up & 0xFC000000) != 0 )
                  return 6;
                return v6;
              }
            }
            else
            {
              *up = s[4] & 0x3F | ((s[3] & 0x3F | ((s[2] & 0x3F | ((s[1] & 0x3F | ((*s & 3) << 6)) << 6)) << 6)) << 6);
              v5 = 0;
              if ( (*up & 0xFFE00000) != 0 )
                return 5;
              return v5;
            }
          }
          else
          {
            *up = s[3] & 0x3F | ((s[2] & 0x3F | ((s[1] & 0x3F | ((*s & 7) << 6)) << 6)) << 6);
            v4 = 0;
            if ( (*up & 0xFFFF0000) != 0 )
              return 4;
            return v4;
          }
        }
        else
        {
          *up = s[2] & 0x3F | ((s[1] & 0x3F | ((*s & 0xF) << 6)) << 6);
          v3 = 0;
          if ( (*up & 0xFFFFF800) != 0 )
            return 3;
          return v3;
        }
      }
      else
      {
        *up = s[1] & 0x3F | ((*s & 0x1F) << 6);
        v2 = 0;
        if ( (*up & 0xFFFFFF80) != 0 )
          return 2;
        return v2;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    *up = (unsigned __int8)*s;
    return 1;
  }
}