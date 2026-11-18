DRMP3_API drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3)
{
    drmp3_uint64 totalPCMFrameCount;

    if (pMP3 == NULL) {
        return 0;
    }

    if (pMP3->totalPCMFrameCount != DRMP3_UINT64_MAX) {
        totalPCMFrameCount = pMP3->totalPCMFrameCount;

        if (totalPCMFrameCount >= pMP3->delayInPCMFrames) {
            totalPCMFrameCount -= pMP3->delayInPCMFrames;
        } else {
            /* The delay is greater than the frame count reported by the Xing/Info tag. Assume it's invalid and ignore. */
        }

        if (totalPCMFrameCount >= pMP3->paddingInPCMFrames) {
            totalPCMFrameCount -= pMP3->paddingInPCMFrames;
        } else {
            /* The padding is greater than the frame count reported by the Xing/Info tag. Assume it's invalid and ignore. */
        }

        return totalPCMFrameCount;
    } else {
        /* Unknown frame count. Need to calculate it. */
        if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, NULL, &totalPCMFrameCount)) {
            return 0;
        }

        return totalPCMFrameCount;
    }
}