double func0(double *data, int len) {
  if (len <= 1) {
    return 0.0;
  }
  double mean = avg_calc(data, len);
  double sd = 0.0;
  for (int i = 0; i < len; i++) {
    sd += (data[i] - mean) * (data[i] - mean);
  }
  sd = sqrt(sd / (len - 1));
  return sd;
}