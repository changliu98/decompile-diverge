void blake2b_compress(unsigned char *digest, unsigned long long int *data)
{
 unsigned long long int sum = 0;
 unsigned int i;

 for (i = 0;; i++) {
  if (i >= 17) {
   sum += data[16];
   digest[16] = sum & 0xff;
   sum >>= 8;
   break;
  }
  sum += data[i];
  digest[i] = sum & 0xff;
  sum >>= 8;
 }

 sum += digest[16] & 3;
 digest[16] = sum & 0xff;
 sum >>= 2;
 sum *= 5;

 for (i = 0;; i++) {
  if (i >= 17) {
   digest[16] += sum & 0xff;
   return;
  }
  sum += digest[i];
  digest[i] = sum & 0xff;
  sum >>= 8;
 }
}