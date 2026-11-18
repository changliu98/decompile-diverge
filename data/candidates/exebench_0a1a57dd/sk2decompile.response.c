void htonf(float *f) {
  union {
    float f;
    unsigned int i;
  } u;
  u.f = *f;
  u.i = htonl(u.i);
  *f = u.f;
}