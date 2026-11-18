int bkm_scale(long *value, int multiplier)
{
    // Check if multiplying *x by scale_factor and then dividing by scale_factor
    // results in the original value of *x, to detect overflow.
    if (*value == (*value * (long)multiplier) / (long)multiplier) {
        // Perform the multiplication if no overflow is detected.
        *value = *value * (long)multiplier;
        return 0; // Success: no overflow occurred.
    }
    return 1; // Failure: overflow detected.
}