void __cdecl zywrleCalcSize(int *pW, int *pH, int level)
{
    // Create a bitmask where the 'level' least significant bits are set to 1.
    // Example: if level == 2, mask == 0b11 (3).
    int mask = (1 << level) - 1;

    // Clear the bits in the width and height that fall within the mask.
    // This effectively rounds the dimensions down to the nearest multiple of 2^level.
    *pW &= ~mask;
    *pH &= ~mask;
}