void
ee_readn(unsigned int addr, struct i2c_smbus_ioctl_data *data)
{
 if (addr > 0x80) {
  data->size = 502;
  return;
 }
 data->size = 0;
 data->addr = (addr << 8) + 0x38000;
}