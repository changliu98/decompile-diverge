/*
 * Calculate the register address for SP_FS_MRT.
 *
 * @param i0 Base index value.
 * @return Calculated register address (base + 0xa996).
 */
uint32_t REG_A6XX_SP_FS_MRT(uint32_t base_index)
{
    return base_index + 0xa996;
}