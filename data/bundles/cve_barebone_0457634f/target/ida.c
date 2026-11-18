void __cdecl vector64_dst_append(RStrBuf *sb, csh *handle, cs_insn *insn, int n, int i)
{
  const char *v5; // rax
  const char *v6; // rax
  const char *v7; // r10
  const char *v8; // rax
  const char *v9; // rax
  const char *v10; // r10
  const char *v11; // rax
  const char *v12; // rax
  RStrBuf *v13; // [rsp+28h] [rbp-C8h]
  const char *v14; // [rsp+38h] [rbp-B8h]
  __int64 v15; // [rsp+48h] [rbp-A8h]
  RStrBuf *v16; // [rsp+50h] [rbp-A0h]
  const char *v17; // [rsp+68h] [rbp-88h]
  __int64 v18; // [rsp+78h] [rbp-78h]
  unsigned __int64 v19; // [rsp+80h] [rbp-70h]
  uint64_t mask; // [rsp+90h] [rbp-60h]
  size_t index; // [rsp+98h] [rbp-58h]
  char *regc; // [rsp+A8h] [rbp-48h]
  int shift; // [rsp+B4h] [rbp-3Ch]
  int size; // [rsp+B8h] [rbp-38h]
  cs_arm64_op op; // [rsp+C0h] [rbp-30h] BYREF
  int ia; // [rsp+D0h] [rbp-20h]
  int na; // [rsp+D4h] [rbp-1Ch]
  cs_insn *insna; // [rsp+D8h] [rbp-18h]
  csh *handlea; // [rsp+E0h] [rbp-10h]
  RStrBuf *sba; // [rsp+E8h] [rbp-8h]

  sba = sb;
  handlea = handle;
  insna = insn;
  na = n;
  ia = i;
  op = insn->detail->arm64.operands[n];
  if ( op.vector_index != -1 )
    ia = op.vector_index;
  if ( op.vas == arm64_vas::ARM64_VAS_INVALID || ia == -1 )
  {
    v11 = cs_reg_name(*handlea, insna->detail->arm64.operands[na].reg);
    v12 = r_str_getf(v11);
    r_strbuf_appendf(sba, "%s", v12);
  }
  else
  {
    size = vector_size(&op);
    shift = size * ia;
    regc = "l";
    if ( size <= 0 )
      v19 = 0LL;
    else
      v19 = (size - 1) % 0x40uLL;
    index = v19;
    if ( v19 >= 0x40 )
      index = 0LL;
    mask = bitmask_by_width[index];
    if ( shift >= 64 )
    {
      shift -= 64;
      regc = "h";
    }
    if ( shift <= 0 || shift >= 64 )
    {
      v13 = sba;
      v8 = cs_reg_name(*handlea, insna->detail->arm64.operands[na].reg);
      v14 = r_str_getf(v8);
      v15 = ~(bitmask_by_width[size % 64 - 1] << shift);
      v9 = cs_reg_name(*handlea, insna->detail->arm64.operands[na].reg);
      v10 = r_str_getf(v9);
      r_strbuf_appendf(v13, "0x%lx,&,%s%s,0x%lx,&,|,%s%s", mask, v14, regc, v15, v10, regc);
    }
    else
    {
      v16 = sba;
      v5 = cs_reg_name(*handlea, insna->detail->arm64.operands[na].reg);
      v17 = r_str_getf(v5);
      v18 = ~(bitmask_by_width[size - 1] << shift);
      v6 = cs_reg_name(*handlea, insna->detail->arm64.operands[na].reg);
      v7 = r_str_getf(v6);
      r_strbuf_appendf(
        v16,
        "%d,SWAP,0x%lx,&,<<,%s%s,0x%lx,&,|,%s%s",
        (unsigned int)shift,
        mask,
        v17,
        regc,
        v18,
        v7,
        regc);
    }
  }
}