xxh_u32 __cdecl XXH32_finalize(xxh_u32 hash, const xxh_u8 *ptr, size_t len, XXH_alignment align)
{
    size_t remaining = len & 0xF;

    // Process 4-byte chunks
    while (remaining >= 4)
    {
        xxh_u32 chunk = XXH_readLE32_align(ptr, align);
        ptr += 4;
        hash = XXH_PRIME32_1 * __ROL4__(hash - XXH_PRIME32_2 * chunk, 17);
        remaining -= 4;
    }

    // Process remaining bytes
    while (remaining > 0)
    {
        hash = XXH_PRIME32_5 * __ROL4__(hash + XXH_PRIME32_3 * *ptr, 11);
        ptr++;
        remaining--;
    }

    return XXH32_avalanche(hash);
}