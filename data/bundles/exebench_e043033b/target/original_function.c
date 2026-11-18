static inline void adjust_interval(double *interval, int test_length)
{
        const int min_samples = 5;

        if (test_length / *interval < min_samples)
                *interval = 1.0 / min_samples;
}