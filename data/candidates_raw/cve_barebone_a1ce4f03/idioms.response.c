int r_anal_op_get(struct r_anal *anal, struct r_anal_op *op, unsigned long addr, unsigned char *buf, int len, struct r_anal_op_mask mask)
{
  int ret;
  struct hex_insn hi;
  unsigned int data;
  hex_init(&hi, 0, sizeof(hi));
  data = hex_get(buf);
  ret = hex_disasm(data, &hi, addr);
  op->size = ret;
  if (ret > 0) {
    op->addr = addr;
    return r_anal_op_set(anal, op);
  }
  return ret;
}