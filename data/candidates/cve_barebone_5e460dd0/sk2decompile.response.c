static bool MACH0_(RAnalOp *op, ut64 addr, ut64 nextaddr) {
  bool ret = parse_chained_fixups(op, addr, nextaddr);
  MACH0_count++;
  return ret;
}