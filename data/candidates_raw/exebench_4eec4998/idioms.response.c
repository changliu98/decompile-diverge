float get_color(int color, float *red, float *green, float *blue)
{
  float color_val = 0.0;
  switch (color & 0x3F)
  {
    case 0x11:
      color_val = *green;
      break;
    case 0x12:
      color_val = green[1];
      break;
    case 0x14:
      color_val = green[2];
      break;
    case 0x10:
      color_val = *red;
      break;
    case 0x11:
      color_val = red[1];
      break;
    case 0x12:
      color_val = red[2];
      break;
    case 0x21:
      color_val = *blue;
      break;
    case 0x22:
      color_val = blue[1];
      break;
    case 0x24:
      color_val = blue[2];
      break;
    case 0x01:
      color_val = *red;
      break;
    case 0x02:
      color_val = red[1];
      break;
    case 0x04:
      color_val = red[2];
      break;
    case 0x08:
      color_val = *green;
      break;
    case 0x10:
      color_val = green[1];
      break;
    case 0x20:
      color_val = green[2];
      break;
    case 0x40:
      color_val = *blue;
      break;
    case 0x80:
      color_val = blue[1];
      break;
    case 0xC0:
      color_val = blue[2];
      break;
    default:
      color_val = 0.0;
      break;
  }
  return (color_val);
}