drflac_bool32 __cdecl drflac__decode_samples(
        drflac_bs *bs,
        drflac_uint32 blockSize,
        drflac_uint32 bitsPerSample,
        drflac_uint8 lpcOrder,
        drflac_int32 *pDecodedSamples)
{
  drflac_int32 sample; // [rsp+1Ch] [rbp-B4h] BYREF
  drflac_int32 coefficients[32]; // [rsp+20h] [rbp-B0h] BYREF
  drflac_int8 lpcShift; // [rsp+A5h] [rbp-2Bh] BYREF
  drflac_uint8 lpcPrecision; // [rsp+A6h] [rbp-2Ah] BYREF
  drflac_uint8 i; // [rsp+A7h] [rbp-29h]
  drflac_int32 *pDecodedSamplesa; // [rsp+A8h] [rbp-28h]
  drflac_uint8 lpcOrdera; // [rsp+B7h] [rbp-19h]
  drflac_uint32 bitsPerSamplea; // [rsp+B8h] [rbp-18h]
  drflac_uint32 blockSizea; // [rsp+BCh] [rbp-14h]
  drflac_bs *bsa; // [rsp+C0h] [rbp-10h]

  bsa = bs;
  blockSizea = blockSize;
  bitsPerSamplea = bitsPerSample;
  lpcOrdera = lpcOrder;
  pDecodedSamplesa = pDecodedSamples;
  for ( i = 0; i < (int)lpcOrdera; ++i )
  {
    if ( !drflac__read_int32(bsa, bitsPerSamplea, &sample) )
      return 0;
    pDecodedSamplesa[i] = sample;
  }
  if ( !drflac__read_uint8(bsa, 4u, &lpcPrecision) )
    return 0;
  if ( lpcPrecision == 15 )
    return 0;
  ++lpcPrecision;
  if ( !drflac__read_int8(bsa, 5u, &lpcShift) )
    return 0;
  if ( lpcShift < 0 )
    return 0;
  memset(coefficients, 0, sizeof(coefficients));
  for ( i = 0; i < (int)lpcOrdera; ++i )
  {
    if ( !drflac__read_int32(bsa, lpcPrecision, &coefficients[i]) )
      return 0;
  }
  return drflac__decode_samples_with_residual(
           bsa,
           bitsPerSamplea,
           blockSizea,
           lpcOrdera,
           lpcShift,
           lpcPrecision,
           coefficients,
           pDecodedSamplesa) != 0;
}