unsigned long do_csum(unsigned char *data, int len, unsigned long csum) {
  int i;
  for (i = 0; i < len; i += 2) {
    if (i & 1)
      csum++;
    else
      csum += data[i];
  }
  return csum;
}