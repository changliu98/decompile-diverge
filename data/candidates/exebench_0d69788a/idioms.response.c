int tens(int *val)
{
  int ret = 0;
  switch(*val / 10)
  {
    case 0:
      ret = 0;
      break;
    case 1:
      switch(*val)
      {
        case 10:
          ret = 3;
          break;
        case 11:
          ret = 6;
          break;
        case 12:
          ret = 6;
          break;
        case 13:
          ret = 8;
          break;
        case 14:
          ret = 8;
          break;
        case 15:
          ret = 7;
          break;
        case 16:
          ret = 7;
          break;
        case 17:
          ret = 9;
          break;
        case 18:
          ret = 8;
          break;
        case 19:
          ret = 8;
          break;
      }
      *val = 0;
      break;
    case 2:
      ret = 6;
      break;
    case 3:
      ret = 6;
      break;
    case 4:
      ret = 5;
      break;
    case 5:
      ret = 5;
      break;
    case 6:
      ret = 5;
      break;
    case 7:
      ret = 7;
      break;
    case 8:
      ret = 6;
      break;
    case 9:
      ret = 6;
      break;
  }
  *val = *val % 10;
  return ret;
}