drflac_bool32 __cdecl drflac__decode_samples(
        drflac_bs *bs,
        drflac_uint32 blockSize,
        drflac_uint32 bitsPerSample,
        drflac_uint8 lpcOrder,
        drflac_int32 *pDecodedSamples)
{
  drflac_int32 sample;
  drflac_int32 coefficients[32];
  drflac_int8 lpcShift;
  drflac_uint8 lpcPrecision;
  drflac_uint8 i;

  // 1. Read warm-up samples
  for ( i = 0; i < lpcOrder; ++i )
  {
    if ( !drflac__read_int32(bs, bitsPerSample, &sample) )
      return 0;
    pDecodedSamples[i] = sample;
  }

  // 2. Read LPC precision
  if ( !drflac__read_uint8(bs, 4u, &lpcPrecision) )
    return 0;
  if ( lpcPrecision == 15 )
    return 0;
  lpcPrecision++; // The precision read from the bitstream is (precision - 1)

  // 3. Read LPC shift
  if ( !drflac__read_int8(bs, 5u, &lpcShift) )
    return 0;
  if ( lpcShift < 0 )
    return 0;

  // 4. Read LPC coefficients
  memset(coefficients, 0, sizeof(coefficients));
  for ( i = 0; i < lpcOrder; ++i )
  {
    if ( !drflac__read_int32(bs, lpcPrecision, &coefficients[i]) )
      return 0;
  }

  // 5. Decode the residual
  return drflac__decode_samples_with_residual(
           bs,
           bitsPerSample,
           blockSize,
           lpcOrder,
           lpcShift,
           lpcPrecision,
           coefficients,
           pDecodedSamples) != 0;
}