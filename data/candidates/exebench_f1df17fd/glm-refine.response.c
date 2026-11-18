int __cdecl FNEGQ(unsigned __int64 *rd, unsigned __int64 *rs2)
{
    // Cast the 64-bit pointers to 128-bit integer pointers to accurately 
    // reflect the 128-bit memory operation taking place.
    unsigned __int128 *dst = (unsigned __int128 *)rd;
    unsigned __int128 *src = (unsigned __int128 *)rs2;

    // Flip the most significant bit (sign bit) of the 128-bit value.
    // 0x8000000000000000ULL << 64 creates the mask for the 127th bit.
    *dst = *src ^ ((unsigned __int128)0x8000000000000000ULL << 64);

    return 1;
}