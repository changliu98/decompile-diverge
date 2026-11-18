drwav_uint64 __cdecl drwav_read_pcm_frames_s32__mulaw(drwav *pWav, drwav_uint64 framesToRead, drwav_int32 *pBufferOut)
{
  drwav_uint64 v4; // [rsp+0h] [rbp-1060h]
  drwav_uint64 framesRead; // [rsp+10h] [rbp-1050h]
  drwav_uint64 samplesRead; // [rsp+20h] [rbp-1040h]
  unsigned int bytesPerSample; // [rsp+28h] [rbp-1038h]
  drwav_uint32 bytesPerFrame; // [rsp+2Ch] [rbp-1034h]
  drwav_uint8 sampleData[4096]; // [rsp+30h] [rbp-1030h] BYREF
  drwav_uint64 totalFramesRead; // [rsp+1038h] [rbp-28h]
  drwav_int32 *pBufferOuta; // [rsp+1040h] [rbp-20h]
  drwav_uint64 framesToReada; // [rsp+1048h] [rbp-18h]
  drwav *pWava; // [rsp+1050h] [rbp-10h]

  pWava = pWav;
  framesToReada = framesToRead;
  pBufferOuta = pBufferOut;
  memset(sampleData, 0, sizeof(sampleData));
  bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
  if ( !bytesPerFrame )
    return 0LL;
  bytesPerSample = bytesPerFrame / pWava->channels;
  if ( !bytesPerSample || bytesPerFrame % pWava->channels )
    return 0LL;
  for ( totalFramesRead = 0LL; framesToReada; totalFramesRead += framesRead )
  {
    v4 = framesToReada >= 0x1000uLL / bytesPerFrame ? 0x1000uLL / bytesPerFrame : framesToReada;
    framesRead = drwav_read_pcm_frames(pWava, v4, sampleData);
    if ( !framesRead )
      break;
    if ( framesRead > v4 )
      _assert_fail(
        "framesRead <= framesToReadThisIteration",
        "func.c",
        0x1F0Au,
        "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)");
    samplesRead = pWava->channels * framesRead;
    if ( bytesPerSample * samplesRead > 0x1000 )
      _assert_fail(
        "0",
        "func.c",
        0x1F0Fu,
        "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)");
    drwav_mulaw_to_s32(pBufferOuta, sampleData, samplesRead);
    pBufferOuta += samplesRead;
    framesToReada -= framesRead;
  }
  return totalFramesRead;
}