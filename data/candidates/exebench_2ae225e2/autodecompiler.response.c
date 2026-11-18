void make_double_bigendian(double *d) {
 union {
  double d;
  unsigned char b[8];
 } p, q;

 p.d = *d;
 q.b[0] = p.b[7];
 q.b[1] = p.b[6];
 q.b[2] = p.b[5];
 q.b[3] = p.b[4];
 q.b[4] = p.b[3];
 q.b[5] = p.b[2];
 q.b[6] = p.b[1];
 q.b[7] = p.b[0];
 *d = q.d;
}