drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav* pWav,
                                              drwav_uint64 framesToRead,
                                              drwav_int32* pBufferOut) {
  drwav_uint64 bytesPerFrame;
  drwav_uint64 bytesPerMulaw;
  drwav_uint64 totalFramesRead;
  drwav_uint64 framesToReadThisIteration;
  drwav_uint64 framesReadThisIteration;
  unsigned char mulawBuffer[4096];
  drwav_uint64 mulawFramesRead;
  drwav_uint64 s32FramesRead;
  memset(mulawBuffer, 0, 4096);
  bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
  if (bytesPerFrame == 0) {
    return 0;
  }
  bytesPerMulaw = bytesPerFrame / pWav->bytesPerSample;
  if (bytesPerMulaw == 0 || bytesPerFrame % pWav->bytesPerSample != 0) {
    return 0;
  }
  totalFramesRead = 0;
  while (framesToRead > 0) {
    framesToReadThisIteration =
        (framesToRead >= (4096 / bytesPerFrame) ? (4096 / bytesPerFrame)
                                                : framesToRead);
    framesReadThisIteration =
        drwav_read_pcm_frames(pWav, framesToReadThisIteration, mulawBuffer);
    if (framesReadThisIteration == 0) {
      break;
    }
    DRWAV_ASSERT(framesReadThisIteration <= framesToReadThisIteration);
    mulawFramesRead = framesReadThisIteration * pWav->bytesPerSample;
    s32FramesRead = mulawFramesRead * bytesPerMulaw;
    DRWAV_ASSERT(s32FramesRead <= 4096);
    drwav_mulaw_to_s32(pBufferOut, mulawBuffer, (size_t)mulawFramesRead);
    pBufferOut += mulawFramesRead;
    framesToRead -= framesReadThisIteration;
    totalFramesRead += framesReadThisIteration;
  }
  return totalFramesRead;
}