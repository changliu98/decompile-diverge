unsigned char *DecompressRTF(FILE_MEMORY *pFile, int *pSize) {
  unsigned char *pHeader;
  unsigned char *pIn;
  unsigned char *pOut;
  unsigned char *pRet;
  unsigned int Size;
  unsigned int UncompressedSize;
  unsigned int Magic;
  unsigned int InPos;
  unsigned int BitPos;
  unsigned int BitMask;
  unsigned int OutPos;
  unsigned int CopyPos;
  unsigned int CopyLen;
  pHeader = calloc(208, 1);
  if (!pHeader) {
    printf("Out of Memory at %s : %i\n", "/work/harness.c", 79);
    return 0;
  }
  memcpy(pHeader,
         "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman "
         "\\fswiss \\fmodern \\fscript \\fdecor MS Sans SerifSymbolArialTimes "
         "New RomanCourier{\\colortbl\\red0\\green0\\blue0\n\r\\par \\pard\\plai"
         "n\\f0\\fs20\\b\\i\\u\\tab\\tx",
         207);
  pIn = pFile->pData;
  if (pFile->Size < 20) {
    printf("File too small\n");
    return 0;
  }
  Size = SwapDWord(pIn, 4);
  UncompressedSize = SwapDWord(pIn + 4, 4);
  Magic = SwapDWord(pIn + 8, 4);
  InPos = 16;
  if (Size != pFile->Size - 4) {
    printf(" Size Mismatch: %u != %i\n", Size, pFile->Size - 4);
    free(pHeader);
    return 0;
  }
  if (Magic == 0x41424344) {
    pOut = calloc(UncompressedSize, 1);
    if (!pOut) {
      printf("Out of Memory at %s : %i\n", "/work/harness.c", 108);
      return 0;
    }
    memcpy(pOut, pIn + 4, UncompressedSize);
    free(pHeader);
    return 0;
  }
  if (Magic != 0x7061636b) {
    printf("Unknown compression type (magic number %x)\n", Magic);
    free(pHeader);
    return 0;
  }
  BitPos = 0;
  BitMask = 0;
  if (UncompressedSize > (0x7fffffff - 207)) {
    printf("Corrupted file\n");
    exit(-1);
  }
  pOut = calloc(UncompressedSize + 207, 1);
  if (!pOut) {
    printf("Out of Memory at %s : %i\n", "/work/harness.c", 120);
    return 0;
  }
  memcpy(pOut, pHeader, 207);
  OutPos = 207;
  while (OutPos < UncompressedSize + 207) {
    if (BitPos++ % 8 == 0)
      BitMask = pIn[InPos++];
    else
      BitMask >>= 1;
    if ((BitMask & 1) == 1) {
      CopyPos = pIn[InPos++];
      CopyLen = pIn[InPos++];
      CopyPos = (CopyPos << 4) | (CopyLen >> 4);
      CopyLen = (CopyLen & 15) + 2;
      CopyPos += (OutPos >> 12) << 12;
      if (CopyPos >= OutPos) CopyPos -= 4096;
      CopyLen += CopyPos;
      while (CopyPos < CopyLen && OutPos < UncompressedSize + 207 &&
             InPos < pFile->Size)
        pOut[OutPos++] = pOut[CopyPos++];
    } else {
      if (OutPos >= UncompressedSize + 207 || InPos >= pFile->Size) {
        printf("Corrupted stream\n");
        exit(-1);
      }
      pOut[OutPos++] = pIn[InPos++];
    }
  }
  pIn = pOut;
  pRet = calloc(UncompressedSize, 1);
  if (!pRet) {
    printf("Out of Memory at %s : %i\n", "/work/harness.c", 158);
    return 0;
  }
  memcpy(pRet, pIn + 207, UncompressedSize);
  free(pIn);
  *pSize = UncompressedSize;
  free(pHeader);
  return pRet;
}