uint ether_hash(uchar *address)
{
  uint result = 0;
  for (int index = 0; index < 6; index++) {
    result = (uint)address[index] + result * 0x1003f;
  }
  return result;
}