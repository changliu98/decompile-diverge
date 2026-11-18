int hexagon_v6_op (RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	int ret;
	HexInsn hi;
	memset (&hi, 0, sizeof (hi));
	ut32 data = r_read_le32 (buf);
	ret = hexagon_disasm_instruction (data, &hi, addr);
	op->size = ret;
	if (ret > 0) {
		op->addr = addr;
		ret = hexagon_anal_instruction (&hi, op);
	}
	return ret;
}