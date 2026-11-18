void __cdecl swi_coortrf2(double *xpo, double *xpn, double sineps, double coseps)
{
  double x_8; // [rsp+8h] [rbp-38h]
  double x_16; // [rsp+10h] [rbp-30h]

  x_8 = xpo[1] * coseps + xpo[2] * sineps;
  x_16 = COERCE_DOUBLE(*((_QWORD *)xpo + 1) ^ 0x8000000000000000LL) * sineps + xpo[2] * coseps;
  *xpn = *xpo;
  xpn[1] = x_8;
  xpn[2] = x_16;
}