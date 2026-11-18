int get_scale(int qscale, int type)
{
  int scale = qscale;
  switch (type)
  {
    case 128:
      scale = (63 - qscale + 2)/4;
      break;
    case 129:
      scale = qscale/2;
      break;
    case 130:
      scale = qscale;
      break;
    case 131:
      scale = qscale/4;
      break;
  }
  return scale;
}