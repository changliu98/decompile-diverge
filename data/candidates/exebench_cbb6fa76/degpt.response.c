int obdRevConvert_47_4B(float input_value, uint *result_a, uint *result_b, uint *result_c, uint *result_d)
{
  // Convert float value to integer by scaling with predefined constants
  *result_a = (uint)(long)((input_value * DAT_00102004) / DAT_00102008);
  return 1;
}