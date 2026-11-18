static int xiph_len(int len) {
  int ret;
  ret = len + (len / 255) + 1;
  return ret;
}