Optimized and annotated for reverse engineering
void __cdecl adjust_interval(double *interval, int test_length)
{
  // 
  // Original logic: if ((double)test_length / *interval < 5.0) *interval = 0.2;
  //
  // Mathematically equivalent (assuming *interval > 0):
  // (test_length / *interval) < 5.0  <=>  test_length < 5.0 * (*interval)  <=>  test_length < 5 * (*interval)
  //
  // This optimization removes the expensive floating-point division and type cast, 
  // replacing it with a much faster integer multiplication.
  //
  
  if (test_length < 5 * (int)*interval)
  {
    *interval = 0.2;
  }
}