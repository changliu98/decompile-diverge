int __cdecl obdRevConvert_31(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  int int_val = (int)val;
  
  *A = (int_val >> 8) & 0xFF; // High byte
  *B = int_val & 0xFF;        // Low byte
  
  // C and D are unused in this function
  return 2;
}