static void get_scl_sda_value(unsigned char port, unsigned char *scl,
                              unsigned char *sda) {
  switch (port) {
    case I2C_PORT_0:
      *scl = I2C_SCL_0;
      *sda = I2C_SDA_0;
      break;
    case I2C_PORT_1:
      *scl = I2C_SCL_1;
      *sda = I2C_SDA_1;
      break;
    case I2C_PORT_2:
      *scl = I2C_SCL_2;
      *sda = I2C_SDA_2;
      break;
    case I2C_PORT_3:
      *scl = I2C_SCL_3;
      *sda = I2C_SDA_3;
      break;
    case I2C_PORT_4:
      *scl = I2C_SCL_4;
      *sda = I2C_SDA_4;
      break;
    case I2C_PORT_5:
      *scl = I2C_SCL_5;
      *sda = I2C_SDA_5;
      break;
    case I2C_PORT_6:
      *scl = I2C_SCL_6;
      *sda = I2C_SDA_6;
      break;
    case I2C_PORT_7:
      *scl = I2C_SCL_7;
      *sda = I2C_SDA_7;
      break;
    default:
      *scl = 0;
      *sda = 0;
      break;
  }
}