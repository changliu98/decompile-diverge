int tens(int *v)

{
  int ret;
  int *v_local;
  
  ret = 0;
  switch(*v / 10) {
  case 0:
    return 0;
  case 1:
    switch(*v) {
    case 10:
      ret = 3;
      break;
    case 0xb:
      ret = 6;
      break;
    case 0xc:
      ret = 6;
      break;
    case 0xd:
      ret = 8;
      break;
    case 0xe:
      ret = 8;
      break;
    case 0xf:
      ret = 7;
      break;
    case 0x10:
      ret = 7;
      break;
    case 0x11:
      ret = 9;
      break;
    case 0x12:
      ret = 8;
      break;
    case 0x13:
      ret = 8;
    }
    *v = 0;
    return ret;
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
  }
  *v = *v % 10;
  return ret;
}