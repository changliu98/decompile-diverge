int __cdecl mode1112(int c, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    // Group the weights to make the math easier to read.
    // The "+ 8" acts as a rounding factor before the division by 16.
    int weighted_sum = (a1 + a3 + a6 + a8) + 
                       2 * (a2 + a4 + a5 + a7) + 
                       4 * c + 
                       8;
    
    // Right-shifting by 4 is equivalent to integer division by 16.
    return weighted_sum >> 4;
}