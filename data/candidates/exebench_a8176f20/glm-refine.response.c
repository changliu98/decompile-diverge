unsigned int __cdecl btcl_reg(unsigned int reg_in, int bitno, unsigned int *reg_out_p)
{
  unsigned int bit_val = (reg_in >> bitno) & 1;
  
  reg_in &= ~(1 << bitno);
  *reg_out_p = reg_in;
  
  return bit_val;
}