uint32_t __cdecl REG_A5XX_VPC_VARYING_INTERP_MODE(uint32_t index)
{
    // 57986 (0xE262) is the base offset for the A5XX VPC_VARYING_INTERP_MODE register block.
    // We add the index to find the specific register for the given varying slot.
    return 0xE262 + index;
}