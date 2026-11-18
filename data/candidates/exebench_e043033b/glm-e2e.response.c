void adjust_interval(double *interval, int count) {
    int min_count = 5;
    double ratio = (double)count / *interval;
    
    // 0xb49(%rip) loads a constant, likely 1.0
    if (1.0 > ratio) {
        // 0xb3b(%rip) loads a constant, likely 5.0
        *interval = 5.0;
    }
}