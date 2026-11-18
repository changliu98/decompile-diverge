int __cdecl func0(int n)
{
    if (n == 0)
        return 1;

    // Check if n is a power of two (and not zero, which is already handled)
    if ((n & (n - 1)) == 0)
        return n;

    // Isolate the lowest set bit of n
    int lowest_set_bit = n & -n;
    
    // Calculate the 0-based bit position of the lowest set bit
    int bit_pos = (int)log2((double)lowest_set_bit);
    
    // Set the bit immediately above the lowest set bit
    return n | (1 << (bit_pos + 1));
}