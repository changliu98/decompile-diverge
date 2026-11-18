uint32_t __cdecl hsv2grb(uint16_t hue, uint8_t sat, uint8_t val)
{
  uint8_t b; // [rsp+11h] [rbp-Fh]
  uint8_t g; // [rsp+12h] [rbp-Eh]
  uint8_t r; // [rsp+13h] [rbp-Dh]
  uint16_t bottom; // [rsp+18h] [rbp-8h]

  bottom = (val * (sat ^ 0xFFu)) >> 8;
  switch ( hue % 0x168u / 0x3C )
  {
    case 0u:
      r = val;
      g = bottom
        + ((((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) & 0x80000000) != 0LL)
        + ((unsigned int)((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) >> 5);
      b = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      break;
    case 1u:
      r = bottom + (int)((60 * (hue / 0x3Cu) - hue + 60) * (val - bottom)) / 60;
      g = val;
      b = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      break;
    case 2u:
      r = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      g = val;
      b = bottom
        + ((((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) & 0x80000000) != 0LL)
        + ((unsigned int)((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) >> 5);
      break;
    case 3u:
      r = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      g = bottom + (int)((60 * (hue / 0x3Cu) - hue + 60) * (val - bottom)) / 60;
      b = val;
      break;
    case 4u:
      r = bottom
        + ((((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) & 0x80000000) != 0LL)
        + ((unsigned int)((unsigned __int64)(2290649225LL * (int)(hue % 0x3Cu * (val - bottom))) >> 32) >> 5);
      g = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      b = val;
      break;
    case 5u:
      r = val;
      g = (unsigned __int16)(val * (sat ^ 0xFF)) >> 8;
      b = bottom + (int)((60 * (hue / 0x3Cu) - hue + 60) * (val - bottom)) / 60;
      break;
    default:
      return b | (r << 8) | (g << 16);
  }
  return b | (r << 8) | (g << 16);
}