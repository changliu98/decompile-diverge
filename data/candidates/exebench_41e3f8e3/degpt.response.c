void table_norm(double *data3_nn,int data3_len,double *data2_nn,int data2_len,long *result,
               int result_len)

{
  int j;
  int i;
  int result_len_local;
  long *result_local;
  int data2_len_local;
  double *data2_nn_local;
  int data3_len_local;
  double *data3_nn_local;
  
  for (i = 0; i < data2_len; i = i + 1) {
    for (j = 0; j < data3_len; j = j + 1) {
      if (data2_nn[i] <= data3_nn[j] && data3_nn[j] != data2_nn[i]) {
        result[j] = result[j] + 1;
      }
    }
  }
  for (i = 0; i < result_len; i = i + 1) {
    if (result[i] == 0) {
      result[i] = 1;
    }
  }
  return;
}