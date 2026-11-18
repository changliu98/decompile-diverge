int __cdecl func0(int n)
{
    // 1. (-n & n) isolates the lowest set bit of n.
    // 2. log2(x) + 1.0 computes the 1-based index of that bit.
    // 3. The cast to int truncates the floating-point result.
    // This is functionally equivalent to finding the position of the lowest set bit.
    return (int)(log2((double)(-n & n)) + 1.0);
}