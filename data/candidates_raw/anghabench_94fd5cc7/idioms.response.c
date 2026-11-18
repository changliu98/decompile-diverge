int get_rate(unsigned char rate)
{
  int i = 0;
  switch(rate & 0x7f){
    case 0x02:
      i = 0;
      break;
    case 0x04:
      i = 1;
      break;
    case 0x0b:
      i = 2;
      break;
    case 0x0c:
      i = 4;
      break;
    case 0x12:
      i = 5;
      break;
    case 0x16:
      i = 3;
      break;
    case 0x18:
      i = 6;
      break;
    case 0x24:
      i = 7;
      break;
    case 0x30:
      i = 8;
      break;
    case 0x48:
      i = 9;
      break;
    case 0x60:
      i = 10;
      break;
    case 0x6c:
      i = 11;
      break;
  }
  return i;
}