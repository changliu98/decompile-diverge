/**
 * @brief Maps a line identifier to corresponding SCL and SDA signal constants.
 *
 * @param line Identifier for the I2C/DDC line (e.g., 0x80 for main I2C, 0x81-0x87 for DDC lines).
 * @param scl Pointer to store the mapped SCL signal constant.
 * @param sda Pointer to store the mapped SDA signal constant.
 */
void get_scl_sda_value(uint8_t bus_id, uint8_t *scl_signal, uint8_t *sda_signal)
{
    switch (bus_id) {
    case 0x80:
        // Main I2C bus
        *scl_signal = (uint8_t)SMU7_I2C_SCL;
        *sda_signal = (uint8_t)SMU7_I2C_SDA;
        break;
    case 0x81:
        // DDC VGA Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDCVGACLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDCVGADATA;
        break;
    case 0x82:
        // DDC 6 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC6CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC6DATA;
        break;
    case 0x83:
        // DDC 5 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC5CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC5DATA;
        break;
    case 0x84:
        // DDC 4 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC4CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC4DATA;
        break;
    case 0x85:
        // DDC 3 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC3CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC3DATA;
        break;
    case 0x86:
        // DDC 2 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC2CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC2DATA;
        break;
    case 0x87:
        // DDC 1 Clock and Data
        *scl_signal = (uint8_t)SMU7_I2C_DDC1CLK;
        *sda_signal = (uint8_t)SMU7_I2C_DDC1DATA;
        break;
    default:
        // Invalid line identifier; reset outputs to null
        *scl_signal = '\0';
        *sda_signal = '\0';
    }
}