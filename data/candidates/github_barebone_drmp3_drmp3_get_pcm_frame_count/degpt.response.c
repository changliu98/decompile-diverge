drmp3_uint64 drmp3_get_pcm_frame_count(drmp3 *mp3Decoder)
{
    // Return 0 if the input pointer is NULL
    if (mp3Decoder == NULL) {
        return 0;
    }
    // If the total PCM frame count has not been calculated yet (indicated by the max uint64 value)
    if (mp3Decoder->totalPCMFrameCount == 0xffffffffffffffff) {
        drmp3_uint64 pcmFrameCount;
        // Attempt to calculate the total PCM frame count
        if (!drmp3_get_mp3_and_pcm_frame_count(mp3Decoder, NULL, &pcmFrameCount)) {
            return 0;
        }
        return pcmFrameCount;
    }
    // Retrieve the cached total PCM frame count
    drmp3_uint64 pcmFrameCount = mp3Decoder->totalPCMFrameCount;
    // Subtract the delay frames if they are within the total count
    if (mp3Decoder->delayInPCMFrames <= pcmFrameCount) {
        pcmFrameCount -= mp3Decoder->delayInPCMFrames;
    }
    // Subtract the padding frames if they are within the total count
    if (mp3Decoder->paddingInPCMFrames <= pcmFrameCount) {
        pcmFrameCount -= mp3Decoder->paddingInPCMFrames;
    }
    // Return the adjusted total PCM frame count
    return pcmFrameCount;
}