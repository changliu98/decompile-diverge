bool __cdecl type_marker_to_cmp_type(uint8_t type_marker, uint8_t *cmp_type)
{
  bool v3; // [rsp+17h] [rbp-1h]

  if ( type_marker > 0x7Fu )
  {
    if ( type_marker > 0x8Fu )
    {
      if ( type_marker > 0x9Fu )
      {
        if ( type_marker > 0xBFu )
        {
          if ( type_marker < 0xE0u )
          {
            switch ( type_marker )
            {
              case 0xC0u:
                *cmp_type = 4;
                v3 = 1;
                break;
              case 0xC2u:
                *cmp_type = 5;
                v3 = 1;
                break;
              case 0xC3u:
                *cmp_type = 5;
                v3 = 1;
                break;
              case 0xC4u:
                *cmp_type = 6;
                v3 = 1;
                break;
              case 0xC5u:
                *cmp_type = 7;
                v3 = 1;
                break;
              case 0xC6u:
                *cmp_type = 8;
                v3 = 1;
                break;
              case 0xC7u:
                *cmp_type = 9;
                v3 = 1;
                break;
              case 0xC8u:
                *cmp_type = 10;
                v3 = 1;
                break;
              case 0xC9u:
                *cmp_type = 11;
                v3 = 1;
                break;
              case 0xCAu:
                *cmp_type = 12;
                v3 = 1;
                break;
              case 0xCBu:
                *cmp_type = 13;
                v3 = 1;
                break;
              case 0xCCu:
                *cmp_type = 14;
                v3 = 1;
                break;
              case 0xCDu:
                *cmp_type = 15;
                v3 = 1;
                break;
              case 0xCEu:
                *cmp_type = 16;
                v3 = 1;
                break;
              case 0xCFu:
                *cmp_type = 17;
                v3 = 1;
                break;
              case 0xD0u:
                *cmp_type = 18;
                v3 = 1;
                break;
              case 0xD1u:
                *cmp_type = 19;
                v3 = 1;
                break;
              case 0xD2u:
                *cmp_type = 20;
                v3 = 1;
                break;
              case 0xD3u:
                *cmp_type = 21;
                v3 = 1;
                break;
              case 0xD4u:
                *cmp_type = 22;
                v3 = 1;
                break;
              case 0xD5u:
                *cmp_type = 23;
                v3 = 1;
                break;
              case 0xD6u:
                *cmp_type = 24;
                v3 = 1;
                break;
              case 0xD7u:
                *cmp_type = 25;
                v3 = 1;
                break;
              case 0xD8u:
                *cmp_type = 26;
                v3 = 1;
                break;
              case 0xD9u:
                *cmp_type = 27;
                v3 = 1;
                break;
              case 0xDAu:
                *cmp_type = 28;
                v3 = 1;
                break;
              case 0xDBu:
                *cmp_type = 29;
                v3 = 1;
                break;
              case 0xDCu:
                *cmp_type = 30;
                v3 = 1;
                break;
              case 0xDDu:
                *cmp_type = 31;
                v3 = 1;
                break;
              case 0xDEu:
                *cmp_type = 32;
                v3 = 1;
                break;
              case 0xDFu:
                *cmp_type = 33;
                v3 = 1;
                break;
              default:
                v3 = 0;
                break;
            }
          }
          else
          {
            *cmp_type = 34;
            return 1;
          }
        }
        else
        {
          *cmp_type = 3;
          return 1;
        }
      }
      else
      {
        *cmp_type = 2;
        return 1;
      }
    }
    else
    {
      *cmp_type = 1;
      return 1;
    }
  }
  else
  {
    *cmp_type = 0;
    return 1;
  }
  return v3;
}