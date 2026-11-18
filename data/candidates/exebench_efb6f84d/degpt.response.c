int obdRevConvert_2D(float inputValue, uint *resultA, uint *unusedB, uint *unusedC, uint *unusedD)
{
  // Convert float value 'val' to an unsigned integer by adding an offset (DAT_00102004)
  // and dividing by a divisor (DAT_00102008), then cast to uint.
  // Store the result in the memory location pointed to by A.
  *resultA = (uint)(long)((inputValue + DAT_00102004) / DAT_00102008);
  
  // Return 1 to indicate successful conversion.
  return 1;
}