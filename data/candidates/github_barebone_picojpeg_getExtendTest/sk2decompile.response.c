unsigned short getExtendTest(unsigned char extend) {
  unsigned short extendTest;
  switch (extend) {
    case 0:
      extendTest = 0;
      break;
    case 1:
      extendTest = 1;
      break;
    case 2:
      extendTest = 2;
      break;
    case 3:
      extendTest = 4;
      break;
    case 4:
      extendTest = 8;
      break;
    case 5:
      extendTest = 16;
      break;
    case 6:
      extendTest = 32;
      break;
    case 7:
      extendTest = 64;
      break;
    case 8:
      extendTest = 128;
      break;
    case 9:
      extendTest = 256;
      break;
    case 10:
      extendTest = 512;
      break;
    case 11:
      extendTest = 1024;
      break;
    case 12:
      extendTest = 2048;
      break;
    case 13:
      extendTest = 4096;
      break;
    case 14:
      extendTest = 8192;
      break;
    case 15:
      extendTest = 16384;
      break;
    default:
      extendTest = 0;
      break;
  }
  return extendTest;
}