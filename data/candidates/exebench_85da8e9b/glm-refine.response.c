void __cdecl unpack_dxt(unsigned __int8 mask, unsigned __int16 col1, unsigned __int16 col2, unsigned __int8 *target)
{
  // Extract 5-bit components and scale them to 8-bit (0-255 range)
  // Red:   bits 0-4   -> << 3
  // Green: bits 5-10  -> << 2 (achieved via >> 3 & 0xFC)
  // Blue:  bits 11-15 -> << 3 (achieved via & 0xF8)
  unsigned __int8 r1 = (col1 & 0x1F) << 3;
  unsigned __int8 g1 = (col1 >> 3) & 0xFC;
  unsigned __int8 b1 = (col1 >> 8) & 0xF8;

  unsigned __int8 r2 = (col2 & 0x1F) << 3;
  unsigned __int8 g2 = (col2 >> 3) & 0xFC;
  unsigned __int8 b2 = (col2 >> 8) & 0xF8;

  switch ( mask )
  {
    case 0:
      target[0] = r1;
      target[1] = g1;
      target[2] = b1;
      break;

    case 1:
      target[0] = r2;
      target[1] = g2;
      target[2] = b2;
      break;

    case 2:
      if ( col1 > col2 )
      {
        // 2/3 color 1 + 1/3 color 2
        target[0] = (2 * r1 + r2) / 3;
        target[1] = (2 * g1 + g2) / 3;
        target[2] = (2 * b1 + b2) / 3;
      }
      else
      {
        // 1/2 color 1 + 1/2 color 2
        target[0] = (r1 + r2) / 2;
        target[1] = (g1 + g2) / 2;
        target[2] = (b1 + b2) / 2;
      }
      break;

    case 3:
      if ( col1 > col2 )
      {
        // 1/3 color 1 + 2/3 color 2
        target[0] = (r1 + 2 * r2) / 3;
        target[1] = (g1 + 2 * g2) / 3;
        target[2] = (b1 + 2 * b2) / 3;
      }
      else
      {
        // Transparent Black
        target[0] = 0;
        target[1] = 0;
        target[2] = 0;
      }
      break;

    default:
      break;
  }
}