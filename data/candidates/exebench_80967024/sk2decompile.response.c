void upcoef_len_cal(int len, int n, int m, int *upcoef_len, int *upcoef_len1) {
  int i;
  *upcoef_len = len;
  *upcoef_len1 = len;
  for (i = 0; i < m; i++) {
    *upcoef_len1 = *upcoef_len1 + n - 1;
    *upcoef_len1 = *upcoef_len1 + n - 1;
    *upcoef_len = *upcoef_len + n - 2;
  }
}