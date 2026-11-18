int __cdecl obdRevConvert_23(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // Calculate the quotient by dividing the value by 10
  int quotient = (int)(float)(val / 10.0);

  // Split the quotient into high and low bytes
  *A = (unsigned int)(quotient / 256LL);
  *B = (unsigned int)(quotient % 256LL);

  // C and D are unused
  return 2;
}