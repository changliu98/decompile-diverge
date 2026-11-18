static drflac_bool32 drflac__decode_samples(drflac_bs* bs,
                                            drflac_uint32 previousFrameSize,
                                            drflac_uint32 bitsPerSample,
                                            drflac_uint8 numberOfChannels,
                                            drflac_uint32* pSamplesOut) {
  drflac_uint32 sample;
  drflac_uint32 bitsPerResidual;
  drflac_int8 residualScale;
  drflac_int8 residualShift;
  drflac_uint32 residuals[32];
  drflac_uint8 i;
  for (i = 0; i < numberOfChannels; ++i) {
    if (!drflac__read_int32(bs, bitsPerSample, &sample)) {
      return 0;
    }
    pSamplesOut[i] = sample;
  }
  if (!drflac__read_uint8(bs, 4, &bitsPerResidual)) {
    return 0;
  }
  if (bitsPerResidual == 15) {
    return 0;
  }
  bitsPerResidual += 1;
  if (!drflac__read_int8(bs, 5, &residualScale)) {
    return 0;
  }
  if (residualScale < 0) {
    return 0;
  }
  memset(residuals, 0, sizeof(residuals));
  for (i = 0; i < numberOfChannels; ++i) {
    if (!drflac__read_int32(bs, bitsPerResidual, &residuals[i])) {
      return 0;
    }
  }
  if (!drflac__decode_samples_with_residual(
          bs, bitsPerSample, previousFrameSize, numberOfChannels, residualScale,
          bitsPerResidual, residuals, pSamplesOut)) {
    return 0;
  }
  return 1;
}