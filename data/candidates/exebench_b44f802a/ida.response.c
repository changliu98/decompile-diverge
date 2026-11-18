void __cdecl YvVfilterCoef(double sigma, double *filter)
{
  double m2sq; // [rsp+0h] [rbp-70h]
  double m1sq; // [rsp+8h] [rbp-68h]
  double scale; // [rsp+48h] [rbp-28h]
  double q; // [rsp+58h] [rbp-18h]

  m1sq = 1.10783 * 1.10783;
  m2sq = 1.40586 * 1.40586;
  if ( sigma >= 3.556 )
    q = (sigma - 3.556) * 0.9804 + 2.5091;
  else
    q = 0.0561 * sigma * sigma + sigma * 0.5784 + -0.2568;
  scale = (q + 1.1668) * (2.0 * 1.10783 * q + m1sq + m2sq + q * q);
  *filter = -(-(q * q) * q / scale);
  filter[1] = -(q * q * (q * 3.0 + 1.10783 + 1.10783 + 1.1668) / scale);
  filter[2] = -(COERCE_DOUBLE(*(_QWORD *)&q ^ 0x8000000000000000LL)
              * (q * q * 3.0 + (1.1668 + 1.1668 + 4.0 * 1.10783) * q + 2.0 * 1.1668 * 1.10783 + m1sq + m2sq)
              / scale);
  filter[3] = 1.1668 * (m1sq + m2sq) / scale;
  filter[4] = -(COERCE_DOUBLE(*(_QWORD *)&q ^ 0x8000000000000000LL)
              * (q * q * 3.0 + (1.1668 + 1.1668 + 4.0 * 1.10783) * q + 2.0 * 1.1668 * 1.10783 + m1sq + m2sq)
              / scale);
  filter[5] = -(q * q * (q * 3.0 + 1.10783 + 1.10783 + 1.1668) / scale);
  filter[6] = -(-(q * q) * q / scale);
}