unsigned int __cdecl frag_num(unsigned int i)
{
    // Align the index down to the nearest multiple of 4
    unsigned int base = i & ~3u; // Equivalent to (i / 4) * 4

    // Calculate the offset within the current 4-element fragment
    unsigned int offset = i & 3u; // Equivalent to i % 4

    // Return the last index of the current fragment
    return base + 3 - offset;
}