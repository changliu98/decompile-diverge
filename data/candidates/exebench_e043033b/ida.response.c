void __cdecl adjust_interval(double *interval, int test_length)
{
  if ( (double)test_length / *interval < 5.0 )
    *interval = 0.2;
}