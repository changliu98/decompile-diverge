drmp3_uint64 __cdecl drmp3_get_pcm_frame_count(drmp3 *pMP3)
{
    drmp3_uint64 totalPCMFrameCount;

    if (!pMP3)
        return 0;

    // If the total frame count hasn't been calculated yet, calculate it now.
    if (pMP3->totalPCMFrameCount == (drmp3_uint64)-1)
    {
        if (drmp3_get_mp3_and_pcm_frame_count(pMP3, NULL, &totalPCMFrameCount))
            return totalPCMFrameCount;
        else
            return 0;
    }

    // Otherwise, use the cached value and adjust for delay and padding.
    totalPCMFrameCount = pMP3->totalPCMFrameCount;
    
    if (totalPCMFrameCount >= pMP3->delayInPCMFrames)
        totalPCMFrameCount -= pMP3->delayInPCMFrames;
        
    if (totalPCMFrameCount >= pMP3->paddingInPCMFrames)
        totalPCMFrameCount -= pMP3->paddingInPCMFrames;

    return totalPCMFrameCount;
}