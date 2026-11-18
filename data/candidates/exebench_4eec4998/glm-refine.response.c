float __cdecl get_color_value(int attr, float *color1, float *color2, float *color3)
{
  float result;

  switch (attr & 0x3F)
  {
    case 9:
      result = color1[0];
      break;
    case 10:
      result = color1[1];
      break;
    case 12:
      result = color1[2];
      break;
    case 17:
      result = color2[0];
      break;
    case 18:
      result = color2[1];
      break;
    case 20:
      result = color2[2];
      break;
    case 33:
      result = color3[0];
      break;
    case 34:
      result = color3[1];
      break;
    case 36:
      result = color3[2];
      break;
    default:
      result = 0.0f;
      break;
  }
  
  return result;
}