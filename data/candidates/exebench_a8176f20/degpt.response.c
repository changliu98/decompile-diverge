uint btcl_reg(uint reg_in,int bitno,uint *reg_out_p)

{
  uint reg_out;
  uchar res;
  uint *reg_out_p_local;
  int bitno_local;
  uint reg_in_local;
  
  *reg_out_p = reg_in ^ 1 << (bitno & 0x1fU);
  return (uint)((reg_in >> (bitno & 0x1fU) & 1) != 0);
}