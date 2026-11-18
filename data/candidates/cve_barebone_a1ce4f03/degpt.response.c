int hexagon_v6_op(RAnal *anal,RAnalOp *op,unsigned_long_long addr,uchar *buf,int len,
                 RAnalOpMask mask)

{
  uint data_00;
  int size;
  uint data;
  HexInsn hi;
  RAnalOpMask mask_local;
  int len_local;
  uchar *buf_local;
  unsigned_long_long addr_local;
  RAnalOp *op_local;
  RAnal *anal_local;
  int local_c;
  
  memset(&hi,0,4);
  data_00 = r_read_le32(buf);
  local_c = hexagon_disasm_instruction(data_00,&hi,(uint)addr);
  op->size = local_c;
  if (0 < local_c) {
    op->addr = addr;
    local_c = hexagon_anal_instruction(&hi,op);
  }
  return local_c;
}