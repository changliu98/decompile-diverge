xxh_u32 XXH32_finalize(xxh_u32 hash, const xxh_u8* ptr, size_t len, XXH_alignment align)
{
    len &= 15;
    while (len >= 4) {
        hash += XXH_readLE32_align(ptr, align) * 2654435761U;
        hash = (((hash) << 17) | ((hash) >> (32 - 17))) * 2246822519U;
        ptr += 4;
        len -= 4;
    }
    while (len > 0) {
        hash += (*ptr++) * 2246822519U;
        hash = (((hash) << 11) | ((hash) >> (32 - 11))) * 2654435761U;
        --len;
    }
    hash = XXH32_avalanche(hash);
    return hash;
}