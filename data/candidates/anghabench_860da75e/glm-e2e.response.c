double rel_stddev_stats(double stddev, double mean) {
    double result = 0.0;
    if (mean != 0.0) {
        result = 100.0 * stddev / mean;
    }
    return result;
}