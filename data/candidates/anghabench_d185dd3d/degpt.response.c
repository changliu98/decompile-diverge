bool pmic_thermal_is_aux(int reg_addr)
{
    // Check if the address is within the valid range [4, 0x40]
    if (reg_addr < 4 || reg_addr > 0x40) {
        return false;
    }
    // Verify that the address offset from 4 is a multiple of 0xc (12)
    if ((reg_addr - 4) % 0xc != 0) {
        return false;
    }
    // For addresses greater than 7 and less than 0x45,
    // check if the offset from 8 is NOT a multiple of 0xc
    if (reg_addr > 7 && reg_addr < 0x45) {
        return (reg_addr - 8) % 0xc != 0;
    }
    // If all checks pass, the address is considered an auxiliary thermal address
    return true;
}