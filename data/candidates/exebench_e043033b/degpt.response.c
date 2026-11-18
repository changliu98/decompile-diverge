// Adjusts the interval value based on the test length.
// If the ratio of test_length to the current interval is less than DAT_00102010,
// the interval is reset to DAT_00102018.
void adjust_interval(double *current_interval, int test_duration)
{
  // Check if the ratio of test_length to the current interval is below the threshold
  if ((double)test_duration / *current_interval < MIN_RATIO_THRESHOLD) {
    // Reset the interval to the default value DAT_00102018
    *current_interval = DEFAULT_INTERVAL;
  }
}