char * func0(int coeff_x, int coeff_y, int target_sum)
{
    int x_value = 0;
    while (true) {
        // If the remaining value after subtracting i*a from n is negative, no solution exists
        if (target_sum < x_value * coeff_x) {
            return "No solution";
        }
        // Check if the remainder (n - i*a) is divisible by b
        if ((target_sum - x_value * coeff_x) % coeff_y == 0) break;
        x_value = x_value + 1;
    }
    // Format the solution string with x=i and y=(n-i*a)/b
    // Casts are used to handle potential overflow or sign issues in the calculation
    sprintf(func0::result, "x = %d, y = %d", (ulong)(uint)x_value, (long)(target_sum - x_value * coeff_x) / (long)coeff_y & 0xffffffff);
    return func0::result;
}