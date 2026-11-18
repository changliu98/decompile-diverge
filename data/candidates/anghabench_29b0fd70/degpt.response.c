// Maps an integer value from one range to another.
// Parameters:
//   x       - The value to map.
//   in_min  - The lower bound of the value's current range.
//   in_max  - The upper bound of the value's current range.
//   out_min - The lower bound of the target range.
//   out_max - The upper bound of the target range.
// Returns:
//   The mapped value as a float.
float map(int value, int input_min, int input_max, float output_min, float output_max) {
    // Calculate the mapped value using floating-point arithmetic.
    // Note: DAT_00102008 appears to be a global variable used in the calculation.
    return (float)(((DAT_00102008 * (double)(output_max - output_min)) / (double)(input_max - input_min)) * (double)(value - input_min) + (double)output_min);
}