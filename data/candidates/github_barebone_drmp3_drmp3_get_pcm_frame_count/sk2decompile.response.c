drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3) {
  drmp3_config* pConfig = (drmp3_config*)pMP3;
  if (pConfig == NULL) {
    return 0;
  }
  if (pConfig->totalPCMFrameCount != ~0) {
    drmp3_uint64 pcmFrameCount = pConfig->totalPCMFrameCount;
    if (pcmFrameCount >= pConfig->totalPCMFrameCountLossy) {
      pcmFrameCount -= pConfig->totalPCMFrameCountLossy;
    }
    if (pcmFrameCount >= pConfig->totalPCMFrameCountLossless) {
      pcmFrameCount -= pConfig->totalPCMFrameCountLossless;
    }
    return pcmFrameCount;
  }
  drmp3_uint64 pcmFrameCount;
  if (drmp3_get_mp3_and_pcm_frame_count(pConfig, NULL, &pcmFrameCount)) {
    return pcmFrameCount;
  }
  return 0;
}