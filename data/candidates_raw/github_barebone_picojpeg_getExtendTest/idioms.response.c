static unsigned short get_val(unsigned char i)
{
  unsigned short val = 0;
  switch(i){
    case 0:
      val = 0;
      break;
    case 1:
      val = 1;
      break;
    case 2:
      val = 2;
      break;
    case 3:
      val = 4;
      break;
    case 4:
      val = 8;
      break;
    case 5:
      val = 16;
      break;
    case 6:
      val = 32;
      break;
    case 7:
      val = 64;
      break;
    case 8:
      val = 128;
      break;
    case 9:
      val = 256;
      break;
    case 10:
      val = 512;
      break;
    case 11:
      val = 1024;
      break;
    case 12:
      val = 2048;
      break;
    case 13:
      val = 4096;
      break;
    case 14:
      val = 8192;
      break;
    case 15:
      val = 16384;
      break;
  }
  return val;
}