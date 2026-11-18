__attribute__((used)) static void vector64_dst_append(RStrBuf *b, csh handle, cs_insn *insn, int reg, int index) {
	cs_arm64_op armop = insn->detail->arm64.operands[reg];
	if (armop.mem.base != -1) {
		index = armop.mem.base;
	}
	int vs = (armop.vas && armop.vas == 1)? 1: 0;
	if (vs && index != -1) {
		ut64 sz = vector_size (&armop);
		ut64 sh = index * sz;
		char *r = "l";
		ut64 m = 64;
		ut64 i;
		if (sz > 0) {
			i = (sz - 1) % m;
		} else {
			i = 0;
		}
		if (i >= 64) {
			i = 0;
		}
		mask = bitmask_by_width[i];
		if (sh >= 64) {
			sh -= 64;
			r = "h";
		}
		if (sh > 0 && sh < 64) {
			r_strbuf_appendf (b, "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s",
				(int)sh, mask, r, r_str_getf (cs_reg_name (handle->cs_handle, insn->detail->arm64.operands[reg].reg)), (bitmask_by_width[sz - 1] << sh) ^ ~0ULL, r_str_getf (cs_reg_name (handle->cs_handle, insn->detail->arm64.operands[reg].reg)), r);
		} else {
			ut64 dim = sz % 64;
			r_strbuf_appendf (b, "0x%lx,&,%s%s,0x%lx,&,|,%s%s",
				mask, r_str_getf (cs_reg_name (handle->cs_handle, insn->detail->arm64.operands[reg].reg)), r, (bitmask_by_width[dim - 1] << sh) ^ ~0ULL, r_str_getf (cs_reg_name (handle->cs_handle, insn->detail->arm64.operands[reg].reg)), r);
		}
	} else {
		r_strbuf_appendf (b, "#%s", r_str_getf (cs_reg_name (handle->cs_handle, insn->detail->arm64.operands[reg].reg)));
	}
}