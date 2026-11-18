drmp3_uint64 __cdecl drmp3_get_pcm_frame_count(drmp3 *pMP3)
{
  drmp3_uint64 totalPCMFrameCount; // [rsp+8h] [rbp-18h] BYREF
  drmp3 *pMP3a; // [rsp+10h] [rbp-10h]

  pMP3a = pMP3;
  if ( !pMP3 )
    return 0LL;
  if ( pMP3a->totalPCMFrameCount == -1LL )
  {
    if ( drmp3_get_mp3_and_pcm_frame_count(pMP3a, 0LL, &totalPCMFrameCount) )
      return totalPCMFrameCount;
    else
      return 0LL;
  }
  else
  {
    totalPCMFrameCount = pMP3a->totalPCMFrameCount;
    if ( totalPCMFrameCount >= pMP3a->delayInPCMFrames )
      totalPCMFrameCount -= pMP3a->delayInPCMFrames;
    if ( totalPCMFrameCount >= pMP3a->paddingInPCMFrames )
      totalPCMFrameCount -= pMP3a->paddingInPCMFrames;
    return totalPCMFrameCount;
  }
}