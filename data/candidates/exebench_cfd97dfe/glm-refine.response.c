int __cdecl obdRevConvert_21(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // Cast the float to a 32-bit signed integer (standard OBD data representation)
  int int_val = (int)val;

  // Extract the high byte and low byte using bitwise operations
  *A = (unsigned int)(int_val >> 8) & 0xFF; // High byte
  *B = (unsigned int)(int_val & 0xFF);      // Low byte

  // C and D are intentionally left unassigned as per original logic

  return 2;
}