void summary(int *arr,int len,double *pos_count,double *neg_count,double *zero_count)

{
  int i;
  int zero_c;
  int neg_c;
  int pos_c;
  double *zero_count_local;
  double *neg_count_local;
  double *pos_count_local;
  int len_local;
  int *arr_local;
  
  pos_c = 0;
  neg_c = 0;
  zero_c = 0;
  for (i = 0; i < len; i = i + 1) {
    if (arr[i] < 1) {
      if (arr[i] < 0) {
        neg_c = neg_c + 1;
      }
      else {
        zero_c = zero_c + 1;
      }
    }
    else {
      pos_c = pos_c + 1;
    }
  }
  *pos_count = (double)pos_c / (double)len;
  *neg_count = (double)neg_c / (double)len;
  *zero_count = (double)zero_c / (double)len;
  return;
}