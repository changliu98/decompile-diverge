void get_filter(double sigma, double filter[7])
{
  double m1 = 1.10783;
  double m2 = 1.40586;
  double m1sq = m1 * m1;
  double m2sq = m2 * m2;
  double q;
  double scale;
  if (sigma < 3.556)
  {
    q = 0.0561 * sigma * sigma + 0.5784 * sigma - 0.2568;
  }
  else
  {
    q = 2.5091 + (sigma - 3.556) * 0.9804;
  }
  scale = 2 * m1 * q + m1sq + m2sq + q * q + 1.1668 * 2;
  filter[0] = -((-(q * q) * q / scale));
  filter[1] = -((-(q * q) * (3 * q + 2 * m1 + m1 + 1.1668) / scale));
  filter[2] = -((-(q * q) * (3 * q + 4 * m1 + 2 * m1 + 2 * m1 + 1.1668 * 2) / scale));
  filter[3] = (m1sq + m2sq) * 1.1668 / scale;
  filter[4] = -((-(q * q) * (3 * q + 4 * m1 + 2 * m1 + 2 * m1 + 1.1668 * 2) / scale));
  filter[5] = -((-(q * q) * (3 * q + 2 * m1 + m1 + 1.1668) / scale));
  filter[6] = -((-(q * q) * q / scale));
}