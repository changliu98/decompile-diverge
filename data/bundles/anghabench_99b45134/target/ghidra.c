void get_scl_sda_value(uint8_t line,uint8_t *scl,uint8_t *sda)

{
  uint8_t *sda_local;
  uint8_t *scl_local;
  uint8_t line_local;
  
  switch(line) {
  case 0x80:
    *scl = (uint8_t)SMU7_I2C_SCL;
    *sda = (uint8_t)SMU7_I2C_SDA;
    break;
  case 0x81:
    *scl = (uint8_t)SMU7_I2C_DDCVGACLK;
    *sda = (uint8_t)SMU7_I2C_DDCVGADATA;
    break;
  case 0x82:
    *scl = (uint8_t)SMU7_I2C_DDC6CLK;
    *sda = (uint8_t)SMU7_I2C_DDC6DATA;
    break;
  case 0x83:
    *scl = (uint8_t)SMU7_I2C_DDC5CLK;
    *sda = (uint8_t)SMU7_I2C_DDC5DATA;
    break;
  case 0x84:
    *scl = (uint8_t)SMU7_I2C_DDC4CLK;
    *sda = (uint8_t)SMU7_I2C_DDC4DATA;
    break;
  case 0x85:
    *scl = (uint8_t)SMU7_I2C_DDC3CLK;
    *sda = (uint8_t)SMU7_I2C_DDC3DATA;
    break;
  case 0x86:
    *scl = (uint8_t)SMU7_I2C_DDC2CLK;
    *sda = (uint8_t)SMU7_I2C_DDC2DATA;
    break;
  case 0x87:
    *scl = (uint8_t)SMU7_I2C_DDC1CLK;
    *sda = (uint8_t)SMU7_I2C_DDC1DATA;
    break;
  default:
    *scl = '\0';
    *sda = '\0';
  }
  return;
}