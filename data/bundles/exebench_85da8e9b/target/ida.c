void __cdecl unpack_dxt(unsigned __int8 mask, unsigned __int16 col1, unsigned __int16 col2, unsigned __int8 *target)
{
  unsigned __int8 v4; // cl
  unsigned __int16 g2; // [rsp+Eh] [rbp-1Ah]
  unsigned __int16 r2; // [rsp+10h] [rbp-18h]
  unsigned __int16 g1; // [rsp+14h] [rbp-14h]
  unsigned __int16 r1; // [rsp+16h] [rbp-12h]

  r1 = 8 * (col1 & 0x1F);
  g1 = (col1 >> 3) & 0xFC;
  r2 = 8 * (col2 & 0x1F);
  g2 = (col2 >> 3) & 0xFC;
  switch ( mask )
  {
    case 0u:
      *target = r1;
      target[1] = g1;
      target[2] = HIBYTE(col1) & 0xF8;
      break;
    case 1u:
      *target = r2;
      target[1] = g2;
      target[2] = HIBYTE(col2) & 0xF8;
      break;
    case 2u:
      if ( col1 <= (int)col2 )
      {
        *target = (r2 + r1) / 2;
        target[1] = (g2 + g1) / 2;
        v4 = ((HIBYTE(col2) & 0xF8) + (HIBYTE(col1) & 0xF8)) / 2;
      }
      else
      {
        *target = (r2 + 2 * r1) / 3;
        target[1] = (g2 + 2 * g1) / 3;
        v4 = ((HIBYTE(col2) & 0xF8) + 2 * (HIBYTE(col1) & 0xF8)) / 3;
      }
      target[2] = v4;
      break;
    case 3u:
      if ( col1 <= (int)col2 )
      {
        target[2] = 0;
        target[1] = 0;
        *target = 0;
      }
      else
      {
        *target = (2 * r2 + r1) / 3;
        target[1] = (2 * g2 + g1) / 3;
        target[2] = (2 * (HIBYTE(col2) & 0xF8) + (HIBYTE(col1) & 0xF8)) / 3;
      }
      break;
    default:
      return;
  }
}