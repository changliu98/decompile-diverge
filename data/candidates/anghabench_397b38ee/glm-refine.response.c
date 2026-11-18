uint32_t __cdecl REG_A3XX_SP_VS_VPC_DST_REG(uint32_t index)
{
    // 8912 is 0x22C0 in hex, which is the base offset for this register block
    return 0x22C0 + index;
}