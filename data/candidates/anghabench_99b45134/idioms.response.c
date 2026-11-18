void get_scl_sda_value(unsigned char line, unsigned char *scl, unsigned char *sda)
{
  switch (line)
  {
    case 0x80:
      *scl = SMU7_I2C_SCL;
      *sda = SMU7_I2C_SDA;
      break;
    case 0x81:
      *scl = SMU7_I2C_DDCVGACLK;
      *sda = SMU7_I2C_DDCVGADATA;
      break;
    case 0x82:
      *scl = SMU7_I2C_DDC6CLK;
      *sda = SMU7_I2C_DDC6DATA;
      break;
    case 0x83:
      *scl = SMU7_I2C_DDC5CLK;
      *sda = SMU7_I2C_DDC5DATA;
      break;
    case 0x84:
      *scl = SMU7_I2C_DDC4CLK;
      *sda = SMU7_I2C_DDC4DATA;
      break;
    case 0x85:
      *scl = SMU7_I2C_DDC3CLK;
      *sda = SMU7_I2C_DDC3DATA;
      break;
    case 0x86:
      *scl = SMU7_I2C_DDC2CLK;
      *sda = SMU7_I2C_DDC2DATA;
      break;
    case 0x87:
      *scl = SMU7_I2C_DDC1CLK;
      *sda = SMU7_I2C_DDC1DATA;
      break;
    default:
      *scl = 0;
      *sda = 0;
      break;
  }
}