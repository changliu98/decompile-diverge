int __cdecl do_map(char *b, int map, char c)
{
  switch ( c )
  {
    case 8:
      if ( (map & 0x80) != 0 )
        *b = 127;
      else
        *b = c;
      return 1;
    case 10:
      if ( (map & 8) != 0 )
      {
        *b = 13;
        return 1;
      }
      else if ( (map & 0x10) != 0 )
      {
        *b = 13;
        b[1] = 10;
        return 2;
      }
      else if ( (map & 0x20) != 0 )
      {
        return 0;
      }
      else
      {
        *b = c;
        return 1;
      }
    case 13:
      if ( (map & 1) != 0 )
      {
        *b = 10;
        return 1;
      }
      else if ( (map & 2) != 0 )
      {
        *b = 13;
        b[1] = 10;
        return 2;
      }
      else if ( (map & 4) != 0 )
      {
        return 0;
      }
      else
      {
        *b = c;
        return 1;
      }
    case 127:
      if ( (map & 0x40) != 0 )
        *b = 8;
      else
        *b = c;
      return 1;
    default:
      *b = c;
      return 1;
  }
}