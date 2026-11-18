int test(int n) {
  int result = 0;
  u32in();
  u32in();
  sp = u32in();
  int *buf = malloc((sp + 1) * sizeof(int));
  if (buf == 0) { result = -1; goto out; }
  buf[0] = 0;
  unsigned int max = 0;
  for (int i = 0; i < sp; ++i) {
    unsigned int x = u32in();
    buf[i + 1] = buf[i] + x;
    if (max < x) max = x;
    if (buf[i + 1] < buf[i]) { result = -1; goto out; }
  }
  result = n;
out:
  free(buf);
  return result;
}