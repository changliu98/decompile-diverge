long long func0(float *arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        double val = (double)arr[i];
        double frac = val - round(val);
        // The bitwise AND with 0x7FFFFFFFFFFFFFFF clears the sign bit, 
        // effectively computing the absolute value of the fractional part.
        if (fabs(frac) < 0.5) {
            if (arr[i] > 0.0f) {
                int rounded = (int)round(val);
                if (rounded % 2 == 1) {
                    sum += (long long)rounded * (long long)round(val);
                }
            }
        }
    }
    return sum;
}