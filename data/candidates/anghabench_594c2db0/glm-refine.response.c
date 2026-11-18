uint32_t __cdecl REG_A5XX_RB_MRT_BUF_INFO(uint32_t mrt_index)
{
    const uint32_t BASE_OFFSET = 0xE152; // 57682 in decimal
    const uint32_t STRIDE      = 7;      // Spacing between each MRT register block

    return BASE_OFFSET + (mrt_index * STRIDE);
}