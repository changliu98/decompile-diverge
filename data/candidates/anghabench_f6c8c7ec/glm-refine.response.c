int __cdecl qcom_nandc_calc_ecc_bytes(int step_size, int strength)
{
  if (strength == 4)
    return 12;
  
  return 16;
}