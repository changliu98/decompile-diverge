// Converts a float value to four unsigned integer components (A, B, C, D)
// Note: Only component A is calculated and assigned; B, C, D remain unchanged
// Calculation: A = (val * DAT_00102004) / DAT_00102008, cast to long then to uint
// Returns 1 to indicate successful conversion
int obdRevConvert_04(float input_value, uint *component_a, uint *component_b, uint *component_c, uint *component_d)
{
  // Compute A by scaling val with DAT_00102004 and dividing by DAT_00102008
  *component_a = (uint)(long)((input_value * scale_factor) / divisor_factor);
  // Return success status
  return 1;
}