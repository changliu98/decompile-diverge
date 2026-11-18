static unsigned char wifirate2_ratetbl_inx(unsigned char rate) {
  unsigned char inx = 0;
  switch (rate & 0x7f) {
    case 2:
      inx = 0;
      break;
    case 4:
      inx = 1;
      break;
    case 11:
      inx = 2;
      break;
    case 12:
      inx = 4;
      break;
    case 18:
      inx = 5;
      break;
    case 22:
      inx = 3;
      break;
    case 24:
      inx = 6;
      break;
    case 36:
      inx = 7;
      break;
    case 48:
      inx = 8;
      break;
    case 72:
      inx = 9;
      break;
    case 96:
      inx = 10;
      break;
    case 108:
      inx = 11;
      break;
  }
  return inx;
}