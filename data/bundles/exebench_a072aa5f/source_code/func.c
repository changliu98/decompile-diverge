#include <stdio.h>

#include <stdlib.h>

void decrypt(unsigned long* v, unsigned long* k) {
  unsigned long v0, v1, sum, i, delta, k0, k1, k2, k3;
  delta=0X9E3779B9;
  k0=k[0]; k1=k[1]; k2=k[2]; k3=k[3];
  v0 = v[0]; v1 = v[1]; sum=0xC6EF3720;

  for (i=0; i<32; i++) {
    v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    sum -= delta;
  }
  v[0]=v0; v[1]=v1;
}
