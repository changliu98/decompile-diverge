int btcl_reg(uint32_t reg_in, int bitno, uint32_t *reg_out_p)
{
  int bit;

  *reg_out_p = reg_in ^ (1 << bitno);
  bit = (reg_in >> bitno) & 1;
  return(bit);
}