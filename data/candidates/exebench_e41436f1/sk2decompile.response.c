void htond(double *d) {
  unsigned int *p;
  unsigned int tmp;
  p = (unsigned int *)d;
  tmp = p[0];
  p[0] = htonl(p[1]);
  p[1] = htonl(tmp);
}