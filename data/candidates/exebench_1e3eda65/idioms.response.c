int Serial_WriteData(int portId, void *data, int length)
{
  return write(portId,data,length);
}