void __cdecl GivensApply(double c, double s, double *z_1, double *z_2)
{
  double w; // [rsp+0h] [rbp-28h]

  w = *z_1 * c + *z_2 * s;
  *z_2 = COERCE_DOUBLE(*(_QWORD *)z_1 ^ 0x8000000000000000LL) * s + *z_2 * c;
  *z_1 = w;
}