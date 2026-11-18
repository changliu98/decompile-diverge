drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3)
{
    drmp3_uint64 mp3FrameCount;
    drmp3_uint64 pcmFrameCount;

    if (pMP3 == NULL) {
        return 0;
    }

    if (pMP3->totalPCMFrameCount != 0xFFFFFFFFFFFFFFFF) {
        pcmFrameCount = pMP3->totalPCMFrameCount;
        if (pcmFrameCount >= pMP3->delayInPCMFrames) {
            pcmFrameCount -= pMP3->delayInPCMFrames;
        }

        if (pcmFrameCount >= pMP3->paddingInPCMFrames) {
            pcmFrameCount -= pMP3->paddingInPCMFrames;
        }

        return pcmFrameCount;
    }

    if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, &mp3FrameCount, &pcmFrameCount)) {
        return 0;
    }

    return pcmFrameCount;
}