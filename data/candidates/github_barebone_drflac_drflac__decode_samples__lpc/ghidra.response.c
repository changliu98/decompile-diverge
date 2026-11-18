drflac_bool32
drflac__decode_samples__lpc
          (drflac_bs *bs,drflac_uint32 blockSize,drflac_uint32 bitsPerSample,drflac_uint8 lpcOrder,
          drflac_int32 *pDecodedSamples)

{
  drflac_bool32 dVar1;
  drflac_int32 sample;
  drflac_int32 coefficients [32];
  drflac_int8 lpcShift;
  drflac_uint8 lpcPrecision;
  drflac_uint8 i;
  drflac_int32 *pDecodedSamples_local;
  drflac_uint8 lpcOrder_local;
  drflac_uint32 bitsPerSample_local;
  drflac_uint32 blockSize_local;
  drflac_bs *bs_local;
  drflac_bool32 local_c;
  
  pDecodedSamples_local = pDecodedSamples;
  lpcOrder_local = lpcOrder;
  bitsPerSample_local = bitsPerSample;
  blockSize_local = blockSize;
  bs_local = bs;
  for (i = '\0'; i < lpcOrder_local; i = i + '\x01') {
    dVar1 = drflac__read_int32(bs_local,bitsPerSample_local,&sample);
    if (dVar1 == 0) {
      return 0;
    }
    pDecodedSamples_local[i] = sample;
  }
  dVar1 = drflac__read_uint8(bs_local,4,&lpcPrecision);
  if (dVar1 == 0) {
    local_c = 0;
  }
  else if (lpcPrecision == '\x0f') {
    local_c = 0;
  }
  else {
    lpcPrecision = lpcPrecision + '\x01';
    dVar1 = drflac__read_int8(bs_local,5,&lpcShift);
    if (dVar1 == 0) {
      local_c = 0;
    }
    else if (lpcShift < '\0') {
      local_c = 0;
    }
    else {
      memset(coefficients,0,0x80);
      for (i = '\0'; i < lpcOrder_local; i = i + '\x01') {
        dVar1 = drflac__read_int32(bs_local,(uint)lpcPrecision,coefficients + (int)(uint)i);
        if (dVar1 == 0) {
          return 0;
        }
      }
      dVar1 = drflac__decode_samples_with_residual
                        (bs_local,bitsPerSample_local,blockSize_local,(uint)lpcOrder_local,
                         (int)lpcShift,(uint)lpcPrecision,coefficients,pDecodedSamples_local);
      if (dVar1 == 0) {
        local_c = 0;
      }
      else {
        local_c = 1;
      }
    }
  }
  return local_c;
}