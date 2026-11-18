__attribute__((used)) static int hexagon_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, ut8 mask) {
	HexInsn hi;
	int ret;

	memset (&hi, 0, sizeof (hi));
	ut32 instr = 0;
	instr = r_read_le32 (buf);

	op->size = hexagon_disasm_instruction (instr, &hi, (int)addr);
	if (op->size < 1) {
		ret = op->size;
		goto beach;
	}

	op->addr = addr;
	ret = hexagon_anal_instruction (&hi, op);

beach:
	return ret;
}