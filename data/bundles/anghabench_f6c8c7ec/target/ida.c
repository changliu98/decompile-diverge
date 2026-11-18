int __cdecl qcom_nandc_calc_ecc_bytes(int step_size, int strength)
{
  int result; // eax

  result = 16;
  if ( strength == 4 )
    return 12;
  return result;
}