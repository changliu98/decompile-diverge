void vector64_dst_append(RStrBuf *sb, csh *handle, cs_insn *insn, int n, int i) {
	cs_arm64_op op = (insn->detail->arm64).operands[n];
	if (op.vector_index != -1) {
		i = op.vector_index;
	}
	if (op.vas != ARM64_VAS_INVALID && i != -1) {
		int size = vector_size (&op);
		int shift = i * size;
		int isvessas = shift >= 64;
		const char *regc = isvessas ? "h" : "l";
		uint64_t mask = bitmask_by_width [(size - 1) % 64];
		if (isvessas) {
			shift -= 64;
		}
		if (shift > 0 && shift < 64) {
			r_strbuf_appendf (sb, "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s", shift, mask,
					r_str_getf (cs_reg_name (*handle, (insn->detail->arm64).operands[n].reg)), regc,
					(bitmask_by_width[63] ^ (bitmask_by_width[size - 1] << shift)),
					r_str_getf (cs_reg_name (*handle, (insn->detail->arm64).operands[n].reg)), regc);
		} else {
			r_strbuf_appendf (sb, "0x%lx,&,%s%s,0x%lx,&,|,%s%s", mask,
					r_str_getf (cs_reg_name (*handle, (insn->detail->arm64).operands[n].reg)), regc,
					(bitmask_by_width[63] ^ (bitmask_by_width[size - 1] << shift)),
					r_str_getf (cs_reg_name (*handle, (insn->detail->arm64).operands[n].reg)), regc);
		}
	} else {
		r_strbuf_appendf (sb, "%s", r_str_getf (cs_reg_name (*handle, (insn->detail->arm64).operands[n].reg)));
	}
}