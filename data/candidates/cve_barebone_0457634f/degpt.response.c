void vector64_dst_append(RStrBuf *sb,csh *handle,cs_insn *insn,int n,int i)

{
  uint64_t uVar1;
  int iVar2;
  cs_arm64_op *pcVar3;
  char *pcVar4;
  ulong uVar5;
  char *pcVar6;
  ulong local_78;
  int dimsize;
  uint64_t mask;
  size_t index;
  size_t s;
  char *regc;
  int shift;
  int size;
  _Bool isvessas;
  cs_arm64_op op;
  int i_local;
  int n_local;
  cs_insn *insn_local;
  csh *handle_local;
  RStrBuf *sb_local;
  
  pcVar3 = (insn->detail->arm64).operands + n;
  op.vector_index = pcVar3->vector_index;
  op.vas = pcVar3->vas;
  op.reg = pcVar3->reg;
  i_local = i;
  if (op.vector_index != -1) {
    i_local = op.vector_index;
  }
  if ((op.vas == ARM64_VAS_INVALID) || (i_local == -1)) {
    pcVar4 = cs_reg_name(*handle,(insn->detail->arm64).operands[n].reg);
    pcVar4 = r_str_getf(pcVar4);
    r_strbuf_appendf(sb,"%s",pcVar4);
  }
  else {
    iVar2 = vector_size(&op);
    shift = i_local * iVar2;
    regc = "l";
    if (iVar2 < 1) {
      local_78 = 0;
    }
    else {
      local_78 = (ulong)(long)(iVar2 + -1) % 0x40;
    }
    index = local_78;
    if (0x3f < local_78) {
      index = 0;
    }
    uVar1 = bitmask_by_width[index];
    if (0x3f < shift) {
      shift = shift + -0x40;
      regc = "h";
    }
    if ((shift < 1) || (0x3f < shift)) {
      pcVar4 = cs_reg_name(*handle,(insn->detail->arm64).operands[n].reg);
      pcVar4 = r_str_getf(pcVar4);
      uVar5 = bitmask_by_width[0x3f] ^ bitmask_by_width[iVar2 % 0x40 + -1] << ((byte)shift & 0x3f);
      pcVar6 = cs_reg_name(*handle,(insn->detail->arm64).operands[n].reg);
      pcVar6 = r_str_getf(pcVar6);
      r_strbuf_appendf(sb,"0x%lx,&,%s%s,0x%lx,&,|,%s%s",uVar1,pcVar4,regc,uVar5,pcVar6,regc);
    }
    else {
      pcVar4 = cs_reg_name(*handle,(insn->detail->arm64).operands[n].reg);
      pcVar4 = r_str_getf(pcVar4);
      uVar5 = bitmask_by_width[0x3f] ^ bitmask_by_width[iVar2 + -1] << ((byte)shift & 0x3f);
      pcVar6 = cs_reg_name(*handle,(insn->detail->arm64).operands[n].reg);
      pcVar6 = r_str_getf(pcVar6);
      r_strbuf_appendf(sb,"%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s",(ulong)(uint)shift,uVar1,pcVar4,
                       regc,uVar5,pcVar6,regc);
    }
  }
  return;
}