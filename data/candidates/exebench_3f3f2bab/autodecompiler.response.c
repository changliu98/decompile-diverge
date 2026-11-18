int __attribute__((visibility("default"))) sboxCHECK(float *a, float *b, int len) {
  int i;
  int ret;

  if (a == NULL || b == NULL) {
    ret = 1;
    goto end;
  }

  for (i = 0; i < len; i++) {
    if (a[i] > b[i]) {
      ret = 0;
      goto end;
    }
  }

  ret = 1;

end:
  return ret;
}