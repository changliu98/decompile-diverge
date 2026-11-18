static void vector64_dst_append(RStrBuf *sb, RAnalOp *op, RAnalEsil *esil,
                                int dst, int dst_size) {
  RAnalValue v = esil->anal->esil.regs[dst];
  if (v.size != -1) {
    dst_size = v.size;
  }
  if (v.type == R_ANAL_VALUE_UNKNOWN || dst_size == -1) {
    r_strbuf_appendf(sb, "%s",
                     r_str_getf(cs_reg_name(op->cs, esil->anal->esil.regs[dst]
                                                             .reg)));
    return;
  }
  int size = vector_size(&v);
  int shift = dst_size * size;
  const char *s = "l";
  size_t idx = size > 0 ? (size - 1) % 64 : 0;
  if (idx >= 64) {
    idx = 0;
  }
  size_t mask = masks[idx];
  if (shift >= 64) {
    shift -= 64;
    s = "h";
  }
  if (shift > 0 && shift < 64) {
    r_strbuf_appendf(sb, "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s", shift, mask,
                     r_str_getf(cs_reg_name(op->cs, esil->anal->esil.regs[dst]
                                                             .reg)));
    return;
  }
  r_strbuf_appendf(sb, "0x%lx,&,%s%s,0x%lx,&,|,%s%s", mask,
                   r_str_getf(cs_reg_name(op->cs, esil->anal->esil.regs[dst]
                                                             .reg)),
                   s, ~(masks[size - 1] << shift),
                   r_str_getf(cs_reg_name(op->cs, esil->anal->esil.regs[dst]
                                                             .reg)),
                   s);
}