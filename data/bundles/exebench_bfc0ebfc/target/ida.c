void __cdecl utf8_int_string(unsigned int unicode_value, char *string)
{
  if ( string )
  {
    *string = 0;
    if ( unicode_value > 0x7F )
    {
      if ( unicode_value > 0x7FF )
      {
        if ( unicode_value > 0xFFFF )
        {
          if ( unicode_value <= 0x1FFFFF )
          {
            *string = (unicode_value >> 18) & 7 | 0xF0;
            string[1] = (unicode_value >> 12) & 0x3F | 0x80;
            string[2] = (unicode_value >> 6) & 0x3F | 0x80;
            string[3] = unicode_value & 0x3F | 0x80;
            string[4] = 0;
          }
        }
        else
        {
          *string = (unicode_value >> 12) & 0xF | 0xE0;
          string[1] = (unicode_value >> 6) & 0x3F | 0x80;
          string[2] = unicode_value & 0x3F | 0x80;
          string[3] = 0;
        }
      }
      else
      {
        *string = (unicode_value >> 6) & 0x1F | 0xC0;
        string[1] = unicode_value & 0x3F | 0x80;
        string[2] = 0;
      }
    }
    else
    {
      *string = unicode_value;
      string[1] = 0;
    }
  }
}