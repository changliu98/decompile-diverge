long drmp3_get_pcm_frame_count(struct _drmp3 *pMP3)
{
  struct _drmp3 *mp3 = pMP3;
  long totalPCMFrameCount = -1;
  if (mp3 == ((void *)0))
    return 0;
  if (mp3->totalPCMFrameCount != -1)
  {
    totalPCMFrameCount = mp3->totalPCMFrameCount;
    if (totalPCMFrameCount >= mp3->delayInPCMFrames)
      totalPCMFrameCount -= mp3->delayInPCMFrames;
    if (totalPCMFrameCount >= mp3->paddingInPCMFrames)
      totalPCMFrameCount -= mp3->paddingInPCMFrames;
    return totalPCMFrameCount;
  }
  if (drmp3_getFrameCount(mp3, ((void *)0), &totalPCMFrameCount))
    return totalPCMFrameCount;
  return 0;
}