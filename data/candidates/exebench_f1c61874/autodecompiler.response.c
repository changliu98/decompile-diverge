void squeeze(crypto_sign_ed25519_ref_sc25519 *r, const crypto_sign_ed25519_ref_sc25519 *x, const crypto_sign_ed25519_ref_sc25519 *y)
{
  unsigned int m;
  unsigned long long acc = 0;

  for(m=0;m<32;m++)
  {
    acc = 0;
    for(unsigned int n=0;n<m;n++)
      acc += (unsigned long long)x->v[n] * y->v[m-n] + r->v[m+n];
    r->v[m] = acc & 255;
    acc >>= 8;
  }

  acc = 0;
  for(unsigned int n=0;n<32;n++)
    acc += (unsigned long long)x->v[n] * y->v[31-n] + r->v[31+n];
  r->v[31] = (acc + r->v[31]) & 127;
  acc = (acc >> 7) * 19;
  for(m=0;m<32;m++)
  {
    acc = 0;
    for(unsigned int n=0;n<m;n++)
      acc += (unsigned long long)x->v[n] * y->v[m-n] + r->v[m+n];
    acc += r->v[m];
    r->v[m] = acc & 255;
    acc >>= 8;
  }
  acc += r->v[31];
  r->v[31] = acc;
}