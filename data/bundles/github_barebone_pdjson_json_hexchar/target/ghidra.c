int hexchar(int c)

{
  int c_local;
  int local_c;
  
  switch(c) {
  case 0x30:
    local_c = 0;
    break;
  case 0x31:
    local_c = 1;
    break;
  case 0x32:
    local_c = 2;
    break;
  case 0x33:
    local_c = 3;
    break;
  case 0x34:
    local_c = 4;
    break;
  case 0x35:
    local_c = 5;
    break;
  case 0x36:
    local_c = 6;
    break;
  case 0x37:
    local_c = 7;
    break;
  case 0x38:
    local_c = 8;
    break;
  case 0x39:
    local_c = 9;
    break;
  default:
    local_c = -1;
    break;
  case 0x41:
  case 0x61:
    local_c = 10;
    break;
  case 0x42:
  case 0x62:
    local_c = 0xb;
    break;
  case 0x43:
  case 99:
    local_c = 0xc;
    break;
  case 0x44:
  case 100:
    local_c = 0xd;
    break;
  case 0x45:
  case 0x65:
    local_c = 0xe;
    break;
  case 0x46:
  case 0x66:
    local_c = 0xf;
  }
  return local_c;
}