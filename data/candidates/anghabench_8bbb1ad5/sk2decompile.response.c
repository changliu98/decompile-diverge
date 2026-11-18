void RewindBitPosition(unsigned int bitPosition, unsigned int *pBitPosition,
                       unsigned char *pBitBuffer) {
  unsigned int bitOffset;
  bitOffset = bitPosition & 0x07;
  pBitBuffer[bitPosition >> 3] &= (1 << bitOffset) - 1;
  *pBitPosition = bitPosition;
}