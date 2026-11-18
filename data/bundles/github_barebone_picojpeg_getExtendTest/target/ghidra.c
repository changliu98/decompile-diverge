uint16 getExtendTest(uint8 i)

{
  uint8 i_local;
  uint16 local_a;
  
  switch(i) {
  case '\0':
    local_a = 0;
    break;
  case '\x01':
    local_a = 1;
    break;
  case '\x02':
    local_a = 2;
    break;
  case '\x03':
    local_a = 4;
    break;
  case '\x04':
    local_a = 8;
    break;
  case '\x05':
    local_a = 0x10;
    break;
  case '\x06':
    local_a = 0x20;
    break;
  case '\a':
    local_a = 0x40;
    break;
  case '\b':
    local_a = 0x80;
    break;
  case '\t':
    local_a = 0x100;
    break;
  case '\n':
    local_a = 0x200;
    break;
  case '\v':
    local_a = 0x400;
    break;
  case '\f':
    local_a = 0x800;
    break;
  case '\r':
    local_a = 0x1000;
    break;
  case '\x0e':
    local_a = 0x2000;
    break;
  case '\x0f':
    local_a = 0x4000;
    break;
  default:
    local_a = 0;
  }
  return local_a;
}