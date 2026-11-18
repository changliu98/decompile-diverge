static int hexagon_v6_op(RAsm *a, RAsmOp *op, ut64 addr, const ut8 *buf, int len, HexagonDisasmMode mode) {
  HexInsn insn;
  int insn_bits;
  int ret;
  memset(&insn, 0, sizeof(insn));
  insn_bits = r_read_le32(buf);
  ret = hexagon_disasm_instruction(insn_bits, &insn, addr);
  op->size = ret;
  if (ret < 1) {
    return ret;
  }
  op->addr = addr;
  return hexagon_anal_instruction(&insn, op);
}