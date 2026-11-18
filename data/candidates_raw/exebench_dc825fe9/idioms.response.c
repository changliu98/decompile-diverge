void get_pos_neg_zero_counts(int *data, int len, double *pos_count, double *neg_count, double *zero_count)
{
  int i;
  int pos_c = 0;
  int neg_c = 0;
  int zero_c = 0;
  for (i = 0; i < len; i++) {
    if (data[i] > 0) {
      pos_c++;
    }
    else if (data[i] < 0) {
      neg_c++;
    }
    else {
      zero_c++;
    }
  }
  *pos_count = (double)pos_c / (double)len;
  *neg_count = (double)neg_c / (double)len;
  *zero_count = (double)zero_c / (double)len;
}