int write_bus(int file_i2c, char *buffer, int length)
{
 return write(file_i2c, buffer, length);
}