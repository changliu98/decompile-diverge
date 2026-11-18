float __cdecl get_color_value(int attr, float *c, float *b, float *g)
{
  float v5; // [rsp+24h] [rbp-4h]

  switch ( attr & 0x3F )
  {
    case 9:
      v5 = *c;
      break;
    case 0xA:
      v5 = c[1];
      break;
    case 0xC:
      v5 = c[2];
      break;
    case 0x11:
      v5 = *b;
      break;
    case 0x12:
      v5 = b[1];
      break;
    case 0x14:
      v5 = b[2];
      break;
    case 0x21:
      v5 = *g;
      break;
    case 0x22:
      v5 = g[1];
      break;
    case 0x24:
      v5 = g[2];
      break;
    default:
      v5 = 0.0;
      break;
  }
  return v5;
}