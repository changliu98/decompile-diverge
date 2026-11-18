xxh_u64 __cdecl XXH64_finalize(xxh_u64 hash, const xxh_u8 *ptr, size_t len, XXH_alignment align)
{
    xxh_u64 val64;
    xxh_u32 val32;
    size_t remaining;

    // Process 8-byte chunks
    for ( remaining = len & 0x1F; remaining >= 8; remaining -= 8 )
    {
        val64 = XXH_readLE64_align(ptr, align);
        ptr += 8;
        hash = XXH_PRIME64_1 * __ROL8__(hash ^ XXH64_round(0LL, val64), 27) - XXH_PRIME64_4;
    }
    
    // Process a 4-byte chunk if present
    if ( remaining >= 4 )
    {
        val32 = XXH_readLE32_align(ptr, align);
        ptr += 4;
        hash = XXH_PRIME64_2 * __ROL8__(hash ^ (XXH_PRIME64_1 * val32), 23) + XXH_PRIME64_3;
        remaining -= 4;
    }
    
    // Process remaining bytes individually
    while ( remaining )
    {
        hash = XXH_PRIME64_1 * __ROL8__(hash ^ (XXH_PRIME64_5 * *ptr), 11);
        ptr++;
        remaining--;
    }
    
    return XXH64_avalanche(hash);
}