
static void encipher(unsigned long *v, unsigned long *k) {
 unsigned long v0=v[0], v1=v[1], i;
 unsigned long sum=0, delta=0x9E3779B9;

 for (i = 0; i < 31; i++) {
  v0 += ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
  sum += delta;
  v1 += ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
 }
 v[0]=v0; v[1]=v1;
}
