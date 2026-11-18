int __cdecl wifirate2_ratetbl_inx(unsigned __int8 rate)
{
  int inx; // [rsp+8h] [rbp-8h]

  inx = 0;
  switch ( rate & 0x7F )
  {
    case 2:
      inx = 0;
      break;
    case 4:
      inx = 1;
      break;
    case 0xB:
      inx = 2;
      break;
    case 0xC:
      inx = 4;
      break;
    case 0x12:
      inx = 5;
      break;
    case 0x16:
      inx = 3;
      break;
    case 0x18:
      inx = 6;
      break;
    case 0x24:
      inx = 7;
      break;
    case 0x30:
      inx = 8;
      break;
    case 0x48:
      inx = 9;
      break;
    case 0x60:
      inx = 10;
      break;
    case 0x6C:
      inx = 11;
      break;
    default:
      return inx;
  }
  return inx;
}