void __cdecl swapIntEndian(int *pInteger)
{
  unsigned char *bytes = (unsigned char *)pInteger;
  unsigned char temp;

  // Swap byte 0 and byte 3
  temp = bytes[0];
  bytes[0] = bytes[3];
  bytes[3] = temp;

  // Swap byte 1 and byte 2
  temp = bytes[1];
  bytes[1] = bytes[2];
  bytes[2] = temp;
}