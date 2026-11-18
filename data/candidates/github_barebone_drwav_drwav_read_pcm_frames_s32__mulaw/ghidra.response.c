drwav_uint64
drwav_read_pcm_frames_s32__mulaw(drwav *pWav,drwav_uint64 framesToRead,drwav_int32 *pBufferOut)

{
  drwav_uint32 dVar1;
  uint uVar2;
  drwav_uint64 dVar3;
  size_t sampleCount;
  ulong local_1068;
  drwav_uint64 framesRead;
  drwav_uint64 framesToReadThisIteration;
  drwav_uint64 samplesRead;
  drwav_uint32 bytesPerSample;
  drwav_uint32 bytesPerFrame;
  drwav_uint8 sampleData [4096];
  drwav_uint64 totalFramesRead;
  drwav_int32 *pBufferOut_local;
  drwav_uint64 framesToRead_local;
  drwav *pWav_local;
  drwav_uint64 local_10;
  
  memset(sampleData,0,0x1000);
  dVar1 = drwav_get_bytes_per_pcm_frame(pWav);
  if (dVar1 == 0) {
    local_10 = 0;
  }
  else {
    uVar2 = dVar1 / pWav->channels;
    if ((uVar2 == 0) || (dVar1 % (uint)pWav->channels != 0)) {
      local_10 = 0;
    }
    else {
      totalFramesRead = 0;
      pBufferOut_local = pBufferOut;
      for (framesToRead_local = framesToRead; framesToRead_local != 0;
          framesToRead_local = framesToRead_local - dVar3) {
        if (framesToRead_local < SUB168((ZEXT816(0) << 0x40 | ZEXT816(0x1000)) / ZEXT416(dVar1),0))
        {
          local_1068 = framesToRead_local;
        }
        else {
          local_1068 = SUB168((ZEXT816(0) << 0x40 | ZEXT816(0x1000)) / ZEXT416(dVar1),0);
        }
        dVar3 = drwav_read_pcm_frames(pWav,local_1068,sampleData);
        if (dVar3 == 0) break;
        if (local_1068 < dVar3) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("framesRead <= framesToReadThisIteration","func.c",0x1f0a,
                        "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"
                       );
        }
        sampleCount = dVar3 * pWav->channels;
        if (0x1000 < sampleCount * uVar2) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","func.c",0x1f0f,
                        "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"
                       );
        }
        drwav_mulaw_to_s32(pBufferOut_local,sampleData,sampleCount);
        pBufferOut_local = pBufferOut_local + sampleCount;
        totalFramesRead = dVar3 + totalFramesRead;
      }
      local_10 = totalFramesRead;
    }
  }
  return local_10;
}