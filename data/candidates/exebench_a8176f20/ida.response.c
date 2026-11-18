unsigned int __cdecl btcl_reg(unsigned int reg_in, int bitno, unsigned int *reg_out_p)
{
  unsigned __int8 v4; // cf

  v4 = _bittestandcomplement((int *)&reg_in, bitno);
  *reg_out_p = reg_in;
  return v4;
}