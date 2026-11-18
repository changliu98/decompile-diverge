void qr_getSize(unsigned m, unsigned n, unsigned *Q_size, unsigned *R_size, unsigned *permSize) {
  Q_size[0] = m;
  Q_size[1] = m;
  R_size[0] = m;
  R_size[1] = n;
  *permSize = n;
}