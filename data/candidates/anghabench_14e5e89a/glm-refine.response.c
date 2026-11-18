uint32_t __cdecl REG_A4XX_VSC_PIPE_DATA_ADDRESS_REG(uint32_t pipe_index)
{
    return 0xC10 + (pipe_index * 4);
}