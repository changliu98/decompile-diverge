static XXH_PUREF xxh_u32
XXH32_finalize(xxh_u32 hash, const xxh_u8* ptr, size_t len, XXH_alignment align)
{
#define XXH_PROCESS1 do {                             \
    hash += (*ptr++) * XXH_PRIME32_5;                 \
    hash = XXH_rotl32(hash, 11) * XXH_PRIME32_1;      \
} while (0)

#define XXH_PROCESS4 do {                             \
    hash += XXH_get32bits(ptr) * XXH_PRIME32_3;       \
    ptr += 4;                                         \
    hash  = XXH_rotl32(hash, 17) * XXH_PRIME32_4;     \
} while (0)

    if (ptr==NULL) XXH_ASSERT(len == 0);

    /* Compact rerolled version; generally faster */
    if (!XXH32_ENDJMP) {
        len &= 15;
        while (len >= 4) {
            XXH_PROCESS4;
            len -= 4;
        }
        while (len > 0) {
            XXH_PROCESS1;
            --len;
        }
        return XXH32_avalanche(hash);
    } else {
         switch(len&15) /* or switch(bEnd - p) */ {
           case 12:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 8:       XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 4:       XXH_PROCESS4;
                         return XXH32_avalanche(hash);

           case 13:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 9:       XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 5:       XXH_PROCESS4;
                         XXH_PROCESS1;
                         return XXH32_avalanche(hash);

           case 14:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 10:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 6:       XXH_PROCESS4;
                         XXH_PROCESS1;
                         XXH_PROCESS1;
                         return XXH32_avalanche(hash);

           case 15:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 11:      XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 7:       XXH_PROCESS4;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 3:       XXH_PROCESS1;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 2:       XXH_PROCESS1;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 1:       XXH_PROCESS1;
                         XXH_FALLTHROUGH;  /* fallthrough */
           case 0:       return XXH32_avalanche(hash);
        }
        XXH_ASSERT(0);
        return hash;   /* reaching this point is deemed impossible */
    }
}