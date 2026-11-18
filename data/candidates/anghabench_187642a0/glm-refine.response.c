uint32_t __cdecl REG_A3XX_RB_MRT_BLEND_CONTROL(uint32_t mrt_index)
{
    return 0x20B7 + (mrt_index * 4);
}