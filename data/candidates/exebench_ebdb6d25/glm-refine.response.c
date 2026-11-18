void __cdecl swi_coortrf2(double *xpo, double *xpn, double sineps, double coseps)
{
  double x_8;
  double x_16;

  // x_8 is the new Y-coordinate (index 1)
  x_8 = xpo[1] * coseps + xpo[2] * sineps;
  
  // x_16 is the new Z-coordinate (index 2)
  // The bitwise XOR with 0x8000000000000000 flips the sign bit of the double, 
  // which is semantically equivalent to multiplying by -1.0.
  x_16 = -xpo[1] * sineps + xpo[2] * coseps;
  
  // The output vector retains the original X-coordinate (index 0)
  *xpn = *xpo;
  xpn[1] = x_8;
  xpn[2] = x_16;
}