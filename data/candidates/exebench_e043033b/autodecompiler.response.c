void adjust_interval(struct timeval *tv, int sample_count)
{
 int min_sample_count = 5;
 if ((double)sample_count / tv->tv_sec < min_sample_count) {
  tv->tv_sec = (double)sample_count / min_sample_count + 0.1;
 }
}