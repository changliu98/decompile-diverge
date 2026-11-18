int get_opcode(uchar *addr,uint *opcode)

{
  int len;
  uint *opcode_local;
  uchar *addr_local;
  
  if (*addr == '\x0f') {
    *opcode = (uint)*(ushort *)addr;
    len = 2;
  }
  else {
    *opcode = (uint)*addr;
    len = 1;
  }
  return len;
}