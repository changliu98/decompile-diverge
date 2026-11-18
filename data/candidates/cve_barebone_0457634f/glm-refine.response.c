void __cdecl vector64_dst_append(RStrBuf *sb, csh *handle, cs_insn *insn, int n, int i)
{
  cs_arm64_op op = insn->detail->arm64.operands[n];
  int ia = i;
  
  if (op.vector_index != -1)
    ia = op.vector_index;

  if (op.vas == arm64_vas::ARM64_VAS_INVALID || ia == -1)
  {
    const char *reg_name = r_str_getf(cs_reg_name(*handle, insn->detail->arm64.operands[n].reg));
    r_strbuf_appendf(sb, "%s", reg_name);
  }
  else
  {
    int size = vector_size(&op);
    int shift = size * ia;
    const char *regc = "l";
    
    size_t index = (size > 0) ? ((size - 1) % 64) : 0;
    if (index >= 64)
      index = 0;
      
    uint64_t mask = bitmask_by_width[index];
    
    if (shift >= 64)
    {
      shift -= 64;
      regc = "h";
    }
    
    const char *reg_name1 = r_str_getf(cs_reg_name(*handle, insn->detail->arm64.operands[n].reg));
    const char *reg_name2 = r_str_getf(cs_reg_name(*handle, insn->detail->arm64.operands[n].reg));
    
    if (shift <= 0 || shift >= 64)
    {
      uint64_t v15 = ~(bitmask_by_width[size % 64 - 1] << shift);
      r_strbuf_appendf(sb, "0x%lx,&,%s%s,0x%lx,&,|,%s%s", mask, reg_name1, regc, v15, reg_name2, regc);
    }
    else
    {
      uint64_t v18 = ~(bitmask_by_width[size - 1] << shift);
      r_strbuf_appendf(
        sb,
        "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s",
        (unsigned int)shift,
        mask,
        reg_name1,
        regc,
        v18,
        reg_name2,
        regc);
    }
  }
}