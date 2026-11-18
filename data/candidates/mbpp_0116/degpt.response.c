int func0(int *digits, int digit_count)
{
    int accumulated_value = 0; // Initialize result to 0
    for (int index = 0; index < digit_count; index++) { // Iterate through each element in the array
        accumulated_value = accumulated_value * 10 + digits[index]; // Accumulate digits to form a number
    }
    return accumulated_value; // Return the computed number
}