double func0(double *data,int len)

{
  double dVar1;
  int i;
  double sd;
  double mean;
  int len_local;
  double *data_local;
  double local_10;
  
  if (len < 2) {
    local_10 = 0.0;
  }
  else {
    dVar1 = avg_calc(data,len);
    sd = 0.0;
    for (i = 0; i < len; i = i + 1) {
      sd = (data[i] - dVar1) * (data[i] - dVar1) + sd;
    }
    local_10 = sqrt(sd / (double)(len + -1));
  }
  return local_10;
}