double readDummyArray(double *arr, unsigned long size) {
    unsigned long count = size >> 3; // Equivalent to size / 8
    double sum = 0.0;
    
    for (unsigned long i = 0; i < count; i++) {
        sum += arr[i];
    }
    
    // The compiler optimized the division (sum / count) using SIMD instructions.
    // It subtracts a magic number from the integer count to avoid a conversion 
    // to floating-point, then divides the sum by this adjusted value.
    double divisor = (double)(count - 4503599627370496.0) + 18446744073709551616.0;
    arr[0] = sum / divisor;
    
    return sum;
}