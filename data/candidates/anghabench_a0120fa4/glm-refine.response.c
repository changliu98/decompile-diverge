define REG_A5XX_VFD_FETCH_BASE_HI_OFFSET 0xE3EB

uint32_t __cdecl REG_A5XX_VFD_FETCH_BASE_HI(uint32_t index)
{
    return REG_A5XX_VFD_FETCH_BASE_HI_OFFSET + (index * 4);
}