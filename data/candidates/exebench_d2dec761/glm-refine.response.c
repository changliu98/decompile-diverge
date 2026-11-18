void __cdecl leer_datos_instruccion(unsigned __int8 inst_h, unsigned __int8 inst_l, int *codigo_inst, int *dir, int *I)
{
  // Cast to 32-bit to prevent unintended sign extension during bit manipulation
  unsigned int inst_h_32 = (unsigned int)inst_h;

  // Extract Immediate/Indirect flag (Bit 10 of the 16-bit instruction)
  *I = (inst_h_32 >> 2) & 1;

  // Extract Opcode (Bits 15:11 of the 16-bit instruction)
  *codigo_inst = inst_h_32 >> 3;

  // Extract 10-bit Address (Bits 9:8 from inst_h, Bits 7:0 from inst_l)
  *dir = inst_l | ((inst_h_32 & 0x3) << 8);
}