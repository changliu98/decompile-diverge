static float get_color_value(int color, float *diffuse, float *specular,
                             float *emission) {
  float value;
  switch (color & 0x3f) {
    case 9:
      value = diffuse[0];
      break;
    case 10:
      value = diffuse[1];
      break;
    case 12:
      value = diffuse[2];
      break;
    case 17:
      value = specular[0];
      break;
    case 18:
      value = specular[1];
      break;
    case 20:
      value = specular[2];
      break;
    case 33:
      value = emission[0];
      break;
    case 34:
      value = emission[1];
      break;
    case 36:
      value = emission[2];
      break;
    default:
      value = 0.0;
      break;
  }
  return value;
}