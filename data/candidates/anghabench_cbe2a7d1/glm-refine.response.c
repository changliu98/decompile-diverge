uint32_t __cdecl REG_A5XX_VPC_SO_BUFFER_OFFSET(uint32_t stream_index)
{
    // Each stream output buffer's offset register is spaced 7 registers apart,
    // starting at base offset 58027.
    return 7 * stream_index + 58027;
}