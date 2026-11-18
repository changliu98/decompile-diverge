void __cdecl get_scl_sda_value(uint8_t line, uint8_t *scl, uint8_t *sda)
{
    // Lookup table mapping line IDs to their respective SCL and SDA values
    static const uint8_t scl_map[] = {
        SMU7_I2C_SCL,
        SMU7_I2C_DDCVGACLK,
        SMU7_I2C_DDC6CLK,
        SMU7_I2C_DDC5CLK,
        SMU7_I2C_DDC4CLK,
        SMU7_I2C_DDC3CLK,
        SMU7_I2C_DDC2CLK,
        SMU7_I2C_DDC1CLK
    };

    static const uint8_t sda_map[] = {
        SMU7_I2C_SDA,
        SMU7_I2C_DDCVGADATA,
        SMU7_I2C_DDC6DATA,
        SMU7_I2C_DDC5DATA,
        SMU7_I2C_DDC4DATA,
        SMU7_I2C_DDC3DATA,
        SMU7_I2C_DDC2DATA,
        SMU7_I2C_DDC1DATA
    };

    // Check if the line falls within the valid 0x80 - 0x87 range
    if (line >= 0x80 && line <= 0x87) 
    {
        uint8_t index = line - 0x80;
        *scl = scl_map[index];
        *sda = sda_map[index];
    }
    else 
    {
        *scl = 0;
        *sda = 0;
    }
}