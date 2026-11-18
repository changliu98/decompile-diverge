int enddata(unsigned char *data, int len) {
  int rem = len & 0x3f;
  int len2 = len - rem;
  if (rem == 0) return 0;
  data[len2 + 1] = rem - 1;
  return len2 + 64;
}