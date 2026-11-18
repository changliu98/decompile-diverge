int get_opcode(unsigned char *mem, int *opcode)
{
 if (mem[0] == 0xf)
 {
  memcpy(opcode,&mem[0],sizeof(int));
  return 2;
 }
 else
 {
  memcpy(opcode,&mem[0],sizeof(int));
  return 1;
 }
}