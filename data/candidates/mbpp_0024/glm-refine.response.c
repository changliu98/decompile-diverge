// Converts an integer representing a binary number (e.g., 1010) into its decimal equivalent (e.g., 10)
int __cdecl binary_to_decimal(int binary_num)
{
    int decimal_val = 0;
    int bit_pos = 0;

    while (binary_num)
    {
        // Extract the least significant digit (0 or 1) and multiply by 2^bit_pos
        decimal_val += (binary_num % 10) * (1 << bit_pos);
        
        // Shift to the next digit
        binary_num /= 10;
        bit_pos++;
    }

    return decimal_val;
}