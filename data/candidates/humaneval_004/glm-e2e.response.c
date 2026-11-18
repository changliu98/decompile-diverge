float func0(float *arr, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    float mean = sum / n;

    float abs_diff_sum = 0.0f;
    for (int i = 0; i < n; i++) {
        // The bitwise AND with 0x7FFFFFFF clears the sign bit, 
        // which is equivalent to taking the absolute value of the float.
        uint32_t bits;
        float diff = arr[i] - mean;
        // Type punning to apply bitwise mask
        memcpy(&bits, &diff, sizeof(bits));
        bits &= 0x7FFFFFFF;
        float abs_diff;
        memcpy(&abs_diff, &bits, sizeof(abs_diff));
        
        abs_diff_sum += abs_diff;
    }

    return abs_diff_sum / n;
}