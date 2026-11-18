int i2c_write(int file_i2c, char *buffer, int length)
{
 return write(file_i2c, buffer, length);
}