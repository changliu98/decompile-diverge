int qcom_nandc_calc_ecc_bytes(int step_size,int strength)

{
  int iVar1;
  int strength_local;
  int step_size_local;
  
  iVar1 = 0x10;
  if (strength == 4) {
    iVar1 = 0xc;
  }
  return iVar1;
}