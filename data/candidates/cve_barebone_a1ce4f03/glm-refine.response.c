int __cdecl hexagon_v6_op(
        RAnal *anal,
        RAnalOp *op,
        unsigned __int64 addr,
        const unsigned __int8 *buf,
        int len,
        RAnalOpMask mask)
{
  HexInsn hi;
  int size;

  // Unused parameters explicitly cast to void to suppress warnings and indicate intent
  (void)anal;
  (void)len;
  (void)mask;

  memset(&hi, 0, sizeof(hi));

  // Read the 32-bit little-endian instruction from the buffer
  unsigned int data = r_read_le32(buf);

  // Disassemble the instruction
  size = hexagon_disasm_instruction(data, &hi, addr);
  op->size = size;

  // If disassembly fails or yields a non-positive size, return early
  if (size <= 0)
    return size;

  op->addr = addr;

  // Analyze the successfully disassembled instruction
  return hexagon_anal_instruction(&hi, op);
}