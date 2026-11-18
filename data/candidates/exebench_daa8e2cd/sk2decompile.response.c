static void poly1305_add(unsigned char *a, const unsigned char *b) {
  unsigned int i;
  unsigned short carry = 0;
  unsigned short sum;
  for (i = 0; i < 17; i++) {
    sum = a[i] + b[i] + carry;
    a[i] = sum & 0xff;
    carry = sum >> 8;
  }
}