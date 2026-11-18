define SECTOR_DEG 60

uint32_t __cdecl hsv2grb(uint16_t hue, uint8_t sat, uint8_t val)
{
  uint8_t r, g, b;
  uint8_t m = (val * (uint8_t)~sat) >> 8;
  uint8_t sector = (hue % HUE_MAX) / SECTOR_DEG;
  uint8_t remainder = hue % SECTOR_DEG;
  uint8_t diff = val - m;

  switch ( sector )
  {
    case 0:
      r = val;
      g = m + (remainder * diff) / SECTOR_DEG;
      b = m;
      break;
    case 1:
      r = m + ((SECTOR_DEG - remainder) * diff) / SECTOR_DEG;
      g = val;
      b = m;
      break;
    case 2:
      r = m;
      g = val;
      b = m + (remainder * diff) / SECTOR_DEG;
      break;
    case 3:
      r = m;
      g = m + ((SECTOR_DEG - remainder) * diff) / SECTOR_DEG;
      b = val;
      break;
    case 4:
      r = m + (remainder * diff) / SECTOR_DEG;
      g = m;
      b = val;
      break;
    case 5:
      r = val;
      g = m;
      b = m + ((SECTOR_DEG - remainder) * diff) / SECTOR_DEG;
      break;
  }
  
  // Pack into 24-bit GRB format (0x00GGRRBB)
  return b | (r << 8) | (g << 16);
}