// Constrain a value 'a' to be within the range [min, max].
// If 'a' is less than 'min', return 'min'.
// If 'a' is greater than 'max', return 'max'.
// Otherwise, return 'a' unchanged.
float constrain(float lower_bound, float upper_bound, float value)
{
    if (value < lower_bound) return lower_bound;
    if (value > upper_bound) return upper_bound;
    return value;
}