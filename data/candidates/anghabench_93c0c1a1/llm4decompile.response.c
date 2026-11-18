uint32_t hsv2grb(uint16_t hue, uint8_t sat, uint8_t val)
{
 uint8_t rising, falling;
 uint8_t top, bottom;
 uint8_t hue_local;
 uint8_t sat_local;
 uint8_t val_local;
 uint8_t r, g, b;

 val_local = val;
 sat_local = sat;
 hue_local = hue;

 top = val_local;
 bottom = val_local - (((val_local * (255 - sat_local)) + 255 / 2) / 255);

 rising = bottom + (((bottom * (6 * (hue_local % 60))) + 255 / 2) / 255);
 falling = bottom + (((bottom * (6 * (60 - (hue_local % 60)))) + 255 / 2) / 255);

 switch (hue_local / 60) {
 case 0:
  r = top;
  g = rising;
  b = falling;
  break;
 case 1:
  r = falling;
  g = top;
  b = rising;
  break;
 case 2:
  r = rising;
  g = top;
  b = falling;
  break;
 case 3:
  r = falling;
  g = rising;
  b = top;
  break;
 case 4:
  r = rising;
  g = falling;
  b = top;
  break;
 case 5:
  r = top;
  g = falling;
  b = rising;
  break;
 }

 return (uint32_t)(((uint32_t)g << 16) | ((uint32_t)r << 8) | ((uint32_t)b));
}