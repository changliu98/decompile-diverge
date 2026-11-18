static int drflac_decode_block(void *pFLAC__StreamDecoder, unsigned int blockSize, unsigned int bitsPerSample, unsigned char lpcOrder, int *pDecodedSamples)
{
  struct drflac_bs *bs = (drflac_bs *) pFLAC__StreamDecoder;
  unsigned int blockSizea = blockSize;
  unsigned int bitsPerSamplea = bitsPerSample;
  unsigned char lpcOrdera = lpcOrder;
  int *pDecodedSamplesa = pDecodedSamples;
  int sample;
  for (unsigned char i = 0; i < lpcOrdera; i++)
  {
    if (!drflac_read_signed(bs, bitsPerSamplea, &sample))
      return 0;
    pDecodedSamplesa[i] = sample;
  }
  unsigned char lpcPrecision;
  if (!drflac_read_unsigned(bs, 4, &lpcPrecision))
    return 0;
  if (lpcPrecision == 15)
    return 0;
  lpcPrecision++;
  int lpcShift;
  if (!drflac_read_signed(bs, 5, &lpcShift))
    return 0;
  if (lpcShift < 0)
    return 0;
  int lpcCoefficients[32];
  drflac_memset(lpcCoefficients, 0, sizeof(lpcCoefficients));
  for (unsigned char i = 0; i < lpcOrdera; i++)
  {
    if (!drflac_read_signed(bs, lpcPrecision, &lpcCoefficients[i]))
      return 0;
  }
  if (!drflac_decode_block_data(bs, bitsPerSamplea, blockSizea,
                                lpcOrdera, lpcShift, lpcPrecision,
                                lpcCoefficients, pDecodedSamplesa))
    return 0;
  return 1;
}