void set_interval(double *interval, int test_length)
{
  if (test_length / *interval < 5.0)
    *interval = 0.2;
}