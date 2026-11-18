bool type_marker_to_cmp_type(unsigned char type_marker,
                             unsigned char *cmp_type) {
  bool ret;
  if (type_marker < 0x80) {
    *cmp_type = 0;
    ret = true;
  } else if (type_marker < 0x90) {
    *cmp_type = 1;
    ret = true;
  } else if (type_marker < 0xa0) {
    *cmp_type = 2;
    ret = true;
  } else if (type_marker < 0xc0) {
    *cmp_type = 3;
    ret = true;
  } else if (type_marker < 0xe0) {
    switch (type_marker) {
      case 0xc0:
        *cmp_type = 4;
        ret = true;
        break;
      case 0xc2:
        *cmp_type = 5;
        ret = true;
        break;
      case 0xc3:
        *cmp_type = 5;
        ret = true;
        break;
      case 0xc4:
        *cmp_type = 6;
        ret = true;
        break;
      case 0xc5:
        *cmp_type = 7;
        ret = true;
        break;
      case 0xc6:
        *cmp_type = 8;
        ret = true;
        break;
      case 0xc7:
        *cmp_type = 9;
        ret = true;
        break;
      case 0xc8:
        *cmp_type = 10;
        ret = true;
        break;
      case 0xc9:
        *cmp_type = 11;
        ret = true;
        break;
      case 0xca:
        *cmp_type = 12;
        ret = true;
        break;
      case 0xcb:
        *cmp_type = 13;
        ret = true;
        break;
      case 0xcc:
        *cmp_type = 14;
        ret = true;
        break;
      case 0xcd:
        *cmp_type = 15;
        ret = true;
        break;
      case 0xce:
        *cmp_type = 16;
        ret = true;
        break;
      case 0xcf:
        *cmp_type = 17;
        ret = true;
        break;
      case 0xd0:
        *cmp_type = 18;
        ret = true;
        break;
      case 0xd1:
        *cmp_type = 19;
        ret = true;
        break;
      case 0xd2:
        *cmp_type = 20;
        ret = true;
        break;
      case 0xd3:
        *cmp_type = 21;
        ret = true;
        break;
      case 0xd4:
        *cmp_type = 22;
        ret = true;
        break;
      case 0xd5:
        *cmp_type = 23;
        ret = true;
        break;
      case 0xd6:
        *cmp_type = 24;
        ret = true;
        break;
      case 0xd7:
        *cmp_type = 25;
        ret = true;
        break;
      case 0xd8:
        *cmp_type = 26;
        ret = true;
        break;
      case 0xd9:
        *cmp_type = 27;
        ret = true;
        break;
      case 0xda:
        *cmp_type = 28;
        ret = true;
        break;
      case 0xdb:
        *cmp_type = 29;
        ret = true;
        break;
      case 0xdc:
        *cmp_type = 30;
        ret = true;
        break;
      case 0xdd:
        *cmp_type = 31;
        ret = true;
        break;
      case 0xde:
        *cmp_type = 32;
        ret = true;
        break;
      case 0xdf:
        *cmp_type = 33;
        ret = true;
        break;
      default:
        ret = false;
        break;
    }
  } else {
    *cmp_type = 34;
    ret = true;
  }
  return ret;
}