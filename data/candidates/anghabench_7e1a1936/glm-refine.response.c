define A4XX_RB_MRT_CONTROL_STRIDE 5

uint32_t __cdecl REG_A4XX_RB_MRT_CONTROL(uint32_t mrt_index)
{
    return A4XX_RB_MRT_CONTROL_BASE + (mrt_index * A4XX_RB_MRT_CONTROL_STRIDE);
}