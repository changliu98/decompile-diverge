static _Bool type_marker_to_cmp_type(unsigned char type_marker, unsigned char *type)
{
  _Bool ret;
  if (type_marker < 0x80) {
    *type = 0;
    ret = 1;
  }
  else if (type_marker < 0x90) {
    *type = 1;
    ret = 1;
  }
  else if (type_marker < 0xa0) {
    *type = 2;
    ret = 1;
  }
  else if (type_marker < 0xc0) {
    *type = 3;
    ret = 1;
  }
  else if (type_marker < 0xe0) {
    switch (type_marker) {
      case 0xc0:
        *type = 4;
        ret = 1;
        break;
      case 0xc2:
        *type = 5;
        ret = 1;
        break;
      case 0xc3:
        *type = 5;
        ret = 1;
        break;
      case 0xc4:
        *type = 6;
        ret = 1;
        break;
      case 0xc5:
        *type = 7;
        ret = 1;
        break;
      case 0xc6:
        *type = 8;
        ret = 1;
        break;
      case 0xc7:
        *type = 9;
        ret = 1;
        break;
      case 0xc8:
        *type = 10;
        ret = 1;
        break;
      case 0xc9:
        *type = 11;
        ret = 1;
        break;
      case 0xca:
        *type = 12;
        ret = 1;
        break;
      case 0xcb:
        *type = 13;
        ret = 1;
        break;
      case 0xcc:
        *type = 14;
        ret = 1;
        break;
      case 0xcd:
        *type = 15;
        ret = 1;
        break;
      case 0xce:
        *type = 16;
        ret = 1;
        break;
      case 0xcf:
        *type = 17;
        ret = 1;
        break;
      case 0xd0:
        *type = 18;
        ret = 1;
        break;
      case 0xd1:
        *type = 19;
        ret = 1;
        break;
      case 0xd2:
        *type = 20;
        ret = 1;
        break;
      case 0xd3:
        *type = 21;
        ret = 1;
        break;
      case 0xd4:
        *type = 22;
        ret = 1;
        break;
      case 0xd5:
        *type = 23;
        ret = 1;
        break;
      case 0xd6:
        *type = 24;
        ret = 1;
        break;
      case 0xd7:
        *type = 25;
        ret = 1;
        break;
      case 0xd8:
        *type = 26;
        ret = 1;
        break;
      case 0xd9:
        *type = 27;
        ret = 1;
        break;
      case 0xda:
        *type = 28;
        ret = 1;
        break;
      case 0xdb:
        *type = 29;
        ret = 1;
        break;
      case 0xdc:
        *type = 30;
        ret = 1;
        break;
      case 0xdd:
        *type = 31;
        ret = 1;
        break;
      case 0xde:
        *type = 32;
        ret = 1;
        break;
      case 0xdf:
        *type = 33;
        ret = 1;
        break;
      case 0xe0:
        *type = 34;
        ret = 1;
        break;
      default:
        ret = 0;
    }
  }
  return ret;
}