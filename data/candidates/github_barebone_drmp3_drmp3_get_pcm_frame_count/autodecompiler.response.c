drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3)
{
    drmp3_uint64 pcmFrameCount;
    if (pMP3 == NULL) {
        return 0;
    }

    if (pMP3->pcmFrameCountTotal != (drmp3_uint64)~0) {

        pcmFrameCount = pMP3->pcmFrameCountTotal;


        if (pcmFrameCount >= pMP3->pcmFrameCountBeforeSeek)
            pcmFrameCount -= pMP3->pcmFrameCountBeforeSeek;

        if (pcmFrameCount >= pMP3->pcmFrameCountAfterSeek)
            pcmFrameCount -= pMP3->pcmFrameCountAfterSeek;

        return pcmFrameCount;
    } else {
        drmp3_uint64 mp3FrameCount;
        if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, &mp3FrameCount, &pcmFrameCount)) {
            return 0;
        }

        return pcmFrameCount;
    }
}