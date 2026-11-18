int __cdecl Serial_WriteData(int portId, unsigned __int8 *data, int length)
{
  return write(portId, data, length);
}