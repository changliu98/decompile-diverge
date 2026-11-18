int FileSwfDecompression(unsigned char *pBuf, unsigned int nBufSize,
                         DETECT_ENGINE_CTX *pEngineCtx,
                         SCInspectionBuffer *pInspectionBuffer, int nDecompress,
                         unsigned int nDecompressedLen,
                         unsigned int nDecompressLen) {
  int nRet = 0;
  int nSwfType = FileIsSwfFile(pBuf, nBufSize);
  if (nSwfType == 1) {
    return 0;
  }
  unsigned int nSwfHeaderLen = 0;
  if (nSwfType == 2) {
    nSwfHeaderLen = 8;
  } else if (nSwfType == 3) {
    nSwfHeaderLen = 17;
  }
  if (nBufSize <= nSwfHeaderLen) {
    DetectEngineSetEvent(pEngineCtx, 1);
    return 0;
  }
  unsigned int nDecompressLen2 = 0;
  if (nDecompressLen == 0 || nDecompressLen > nBufSize - nSwfHeaderLen) {
    nDecompressLen2 = nBufSize - nSwfHeaderLen;
  } else {
    nDecompressLen2 = nDecompressLen;
  }
  unsigned char nSwfVersion = FileGetSwfVersion(pBuf, nBufSize);
  if ((nSwfType == 2 && nSwfVersion < 6) ||
      (nSwfType == 3 && nSwfVersion < 13)) {
    DetectEngineSetEvent(pEngineCtx, 2);
    return 0;
  }
  unsigned int nDecompressedLen2 = FileGetSwfDecompressedLen(pBuf, nBufSize);
  if (nDecompressedLen2 == 0) {
    nDecompressedLen2 = 2920;
  }
  unsigned int nDecompressedLen3 =
      nDecompressedLen == 0 ? nDecompressedLen2 : nDecompressedLen;
  unsigned int nDecompressedLen4 = nDecompressedLen3 + 8;
  SCInspectionBufferCheckAndExpand(pInspectionBuffer, nDecompressedLen4);
  if (pInspectionBuffer->nSize < nDecompressedLen4) {
    DetectEngineSetEvent(pEngineCtx, 3);
    return 0;
  }
  pInspectionBuffer->nUsed = nDecompressedLen4;
  pInspectionBuffer->pBuf[0] = 'F';
  pInspectionBuffer->pBuf[1] = 'W';
  pInspectionBuffer->pBuf[2] = 'S';
  pInspectionBuffer->pBuf[3] = nSwfVersion;
  *(unsigned int *)(pInspectionBuffer->pBuf + 4) = nDecompressedLen2;
  memset(pInspectionBuffer->pBuf + 8, 0, nDecompressedLen4 - 8);
  if ((nDecompress == 1 || nDecompress == 3) && nSwfType == 2) {
    nRet = FileSwfZlibDecompression(
        pEngineCtx, pBuf + nSwfHeaderLen, nDecompressLen2,
        pInspectionBuffer->pBuf + 8, pInspectionBuffer->nUsed - 8);
    if (nRet != 0) {
      pInspectionBuffer->pBuf2 = pInspectionBuffer->pBuf;
      pInspectionBuffer->nUsed2 = pInspectionBuffer->nUsed;
      return 1;
    }
  } else if ((nDecompress == 2 || nDecompress == 3) && nSwfType == 3) {
    nDecompressLen2 += 13;
    unsigned char pBuf2[nDecompressLen2];
    pBuf2[0] = pBuf[3];
    pBuf2[4] = pBuf[16];
    memset(pBuf2 + 5, 0xff, 8);
    memcpy(pBuf2 + 13, pBuf + nSwfHeaderLen, nDecompressLen2 - 13);
    nRet = FileSwfLzmaDecompression(
        pEngineCtx, pBuf2, nDecompressLen2, pInspectionBuffer->pBuf + 8,
        pInspectionBuffer->nUsed - 8);
    if (nRet == 0) {
      pInspectionBuffer->pBuf2 = pInspectionBuffer->pBuf;
      pInspectionBuffer->nUsed2 = pInspectionBuffer->nUsed;
      return 1;
    }
  }
  return 0;
}