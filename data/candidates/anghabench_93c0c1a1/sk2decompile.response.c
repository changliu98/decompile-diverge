unsigned hsv2grb(unsigned h, unsigned s, unsigned v) {
  unsigned r, g, b;
  unsigned c = (s ^ 0xff) * v >> 8;
  unsigned hue = h % 360;
  unsigned hue_segment = hue / 60;
  unsigned hue_offset = hue % 60;
  switch (hue_segment) {
    case 0:
      r = v;
      g = c + (v - c) * hue_offset / 60;
      b = c;
      break;
    case 1:
      r = c + (v - c) * (60 - hue_offset) / 60;
      g = v;
      b = c;
      break;
    case 2:
      r = c;
      g = v;
      b = c + (v - c) * hue_offset / 60;
      break;
    case 3:
      r = c;
      g = c + (v - c) * (60 - hue_offset) / 60;
      b = v;
      break;
    case 4:
      r = c + (v - c) * hue_offset / 60;
      g = c;
      b = v;
      break;
    case 5:
      r = v;
      g = c;
      b = c + (v - c) * (60 - hue_offset) / 60;
      break;
  }
  return (r << 16) | (g << 8) | b;
}