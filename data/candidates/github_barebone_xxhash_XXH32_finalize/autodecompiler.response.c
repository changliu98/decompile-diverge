static xxh_u32
XXH32_finalize(xxh_u32 h32, const xxh_u8* p, size_t len, XXH_alignment align)
{
    if (p==NULL) p = (const xxh_u8*)(&len);

    len &= 15;
    while (len >= 4) {
        h32 += XXH_readLE32_align(p, align) * 0xC2B2AE3DU;
        p += 4;
        h32 = ((h32 << 17) | (h32 >> (32 - 17))) * 0x27D4EB2FU;
        len -= 4;
    }

    while (len--) {
        h32 += (*p++) * 0x165667B1U;
        h32 = ((h32 << 11) | (h32 >> (32 - 11))) * 0x9E3779B1U;
    }

    return XXH32_avalanche(h32);
}