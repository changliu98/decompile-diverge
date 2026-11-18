void adjust_interval(double *interval,int test_length)

{
  int min_samples;
  int test_length_local;
  double *interval_local;
  
  if ((double)test_length / *interval < DAT_00102010) {
    *interval = DAT_00102018;
  }
  return;
}