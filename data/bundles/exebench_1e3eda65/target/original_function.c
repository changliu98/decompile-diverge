int Serial_WriteData(int portId, unsigned char *data, int length)
{
  return (write(portId, data, length));
}