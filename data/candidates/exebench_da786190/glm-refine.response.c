void __cdecl SetBitInt(int *x, const int bitNum)
{
    // Create a bitmask by shifting 1 to the left by bitNum positions.
    // Perform a bitwise OR assignment to set the target bit in *x.
    *x |= (1 << bitNum);
}