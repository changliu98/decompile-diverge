int func0(int number)
{
    // Calculate the position of the least significant bit (LSB) of n
    // n & -n isolates the LSB (e.g., if n = 12 (1100), n & -n = 4 (100))
    // log2 of that value gives the 0-based index of the LSB
    // Add a constant offset (_DAT_00102008) to the result
    return (int)(log2((double)(number & -number)) + offset_constant);
}