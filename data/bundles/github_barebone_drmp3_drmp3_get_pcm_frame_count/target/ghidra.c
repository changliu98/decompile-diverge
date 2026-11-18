drmp3_uint64 drmp3_get_pcm_frame_count(drmp3 *pMP3)

{
  drmp3_bool32 dVar1;
  drmp3_uint64 totalPCMFrameCount;
  drmp3 *pMP3_local;
  drmp3_uint64 local_10;
  
  if (pMP3 == (drmp3 *)0x0) {
    local_10 = 0;
  }
  else if (pMP3->totalPCMFrameCount == 0xffffffffffffffff) {
    pMP3_local = pMP3;
    dVar1 = drmp3_get_mp3_and_pcm_frame_count(pMP3,(drmp3_uint64 *)0x0,&totalPCMFrameCount);
    if (dVar1 == 0) {
      local_10 = 0;
    }
    else {
      local_10 = totalPCMFrameCount;
    }
  }
  else {
    totalPCMFrameCount = pMP3->totalPCMFrameCount;
    if (pMP3->delayInPCMFrames <= totalPCMFrameCount) {
      totalPCMFrameCount = totalPCMFrameCount - pMP3->delayInPCMFrames;
    }
    if (pMP3->paddingInPCMFrames <= totalPCMFrameCount) {
      totalPCMFrameCount = totalPCMFrameCount - pMP3->paddingInPCMFrames;
    }
    local_10 = totalPCMFrameCount;
  }
  return local_10;
}