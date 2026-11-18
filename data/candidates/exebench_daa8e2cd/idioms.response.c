void poly1305_add(unsigned char *mac, unsigned char *add)
{
  unsigned int i;
  unsigned short carry = 0;
  for (i = 0; i < 17 / 2; i++) {
    unsigned short sum = mac[i] + add[i] + carry;
    mac[i] = sum & 0xff;
    carry = sum >> 8;
  }
}