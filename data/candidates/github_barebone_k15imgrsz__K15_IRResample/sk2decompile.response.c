K15_INT32 K15_IRResample(K15_IRResampleContext* pContext) {
  K15_IRResampleMethod method = pContext->method;
  const K15_INT16* pSrc;
  if (pContext->pSrc) {
    pSrc = pContext->pSrc;
  } else {
    pSrc = pContext->pSrcBuffer;
  }
  K15_INT16* pDst = pContext->pDstBuffer;
  K15_UINT32 srcWidth = pContext->srcWidth;
  K15_UINT32 srcHeight = pContext->srcHeight;
  K15_UINT32 dstWidth = pContext->dstWidth;
  K15_UINT32 dstHeight = pContext->dstHeight;
  K15_IRResampleFilter filter = pContext->filter;
  K15_IRResampleFormat format = pContext->format;
  memset(pDst, 0, srcWidth * K15_IRResampleFormatSize[format] * dstHeight);
  if (method == K15_IRResampleMethod_NearestNeighbour) {
    K15_IRSampleNearestNeighbour(pSrc, pDst, dstWidth, srcHeight, srcWidth,
                                 dstHeight, format);
  } else if (method == K15_IRResampleMethod_Bilinear ||
             method == K15_IRResampleMethod_Bicubic) {
    K15_UINT32 tempBufferSize =
        srcWidth * K15_IRResampleFormatSize[format] * srcHeight;
    K15_INT16* pTempBuffer = (K15_INT16*)malloc(tempBufferSize);
    memset(pTempBuffer, 0, tempBufferSize);
    if (method == K15_IRResampleMethod_Bilinear) {
      K15_IRHorizontallySampleBilinear(pSrc, pTempBuffer, dstWidth, srcHeight,
                                       srcWidth, srcHeight, format, filter);
      K15_IRHorizontallySampleBilinear(pTempBuffer, pDst, srcHeight, srcWidth,
                                       dstHeight, dstWidth, format, filter);
    } else {
      K15_IRHorizontallySampleBicubic(pSrc, pTempBuffer, dstWidth, srcHeight,
                                      srcWidth, srcHeight, format, filter);
      K15_IRHorizontallySampleBicubic(pTempBuffer, pDst, srcHeight, srcWidth,
                                      dstHeight, dstWidth, format, filter);
    }
  }
  return 0;
}