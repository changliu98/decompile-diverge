void pinvJ(double u, double v, double w, double p, double q, double *J) {
  int i;
  double norm;
  J[0] = u * (w * w + q * q) - v * (p * q);
  J[1] = v * (w * w + p * p) - u * (p * q);
  J[2] = w * (w * w + p * p + q * q);
  J[3] = -w * (u * p + v * q);
  J[4] = p * (v * v + w * w) - u * v * q;
  J[5] = -u * v * p + q * (u * u + w * w);
  J[6] = J[3];
  J[7] = w * (u * u + v * v + w * w);
  norm = u * J[0] + v * J[1] + w * J[2];
  for (i = 0; i < 8; i++) J[i] /= norm;
}