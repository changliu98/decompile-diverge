xxh_u32 XXH32_round(xxh_u32 acc, xxh_u32 input)
{
    acc += input * 2654435761U;
    acc = (((acc) << (13)) | ((acc) >> (32 - (13))));
    acc *= 2246822519U;
# 1140 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/LWJGL-CI/lwjgl3/refs/heads/master/3rdparty/xxhash/xxhash.h"
    return acc;
}