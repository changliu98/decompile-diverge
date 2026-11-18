static drwav_uint64 drwav_read_pcm_frames_s32__mulaw(struct drwav *wav, drwav_uint64 framesToRead, int *pBufferOut)
{
    struct drwav_int16 sampleData[-1];
    drwav_uint32 bytesPerFrame;
    drwav_uint32 bytesPerSample;
    drwav_uint64 framesRead;
    drwav_uint64 totalFramesRead = 0;
    drwav_uint64 framesToReadThisIteration;
    drwav_uint64 samplesRead;
    drwav_zero(sampleData, sizeof(sampleData));
    bytesPerFrame = drwav_get_bytes_per_frame(wav);
    if (bytesPerFrame == 0)
        return 0;
    bytesPerSample = bytesPerFrame / wav->channels;
    if (bytesPerSample == 0 || bytesPerFrame % wav->channels != 0)
        return 0;
    while (framesToRead > 0)
    {
        framesToReadThisIteration = (drwav_uint64)(framesToRead < (1024 * 4 / sizeof(drwav_int16)) / bytesPerFrame ? framesToRead : (1024 * 4 / sizeof(drwav_int16)) / bytesPerFrame);
        framesRead = drwav_read_pcm_frames(wav, framesToReadThisIteration, sampleData);
        if (framesRead == 0)
            break;
        ((void) sizeof ((framesRead <= framesToReadThisIteration) ? 1 : 0), __extension__ ({ if (framesRead <= framesToReadThisIteration) ; else __assert_fail ("framesRead <= framesToReadThisIteration", "func.c", 5010, __extension__ __PRETTY_FUNCTION__); }));
        samplesRead = framesRead * wav->channels;
        ((void) sizeof ((samplesRead * bytesPerSample < (1024 * 4 / sizeof(drwav_int16))) ? 1 : 0), __extension__ ({ if (samplesRead * bytesPerSample < (1024 * 4 / sizeof(drwav_int16))) ; else __assert_fail ("0", "func.c", 5015, __extension__ __PRETTY_FUNCTION__); }));
        drwav_int16_to_int32(pBufferOut, sampleData, samplesRead);
        pBufferOut += samplesRead;
        framesToRead -= framesRead;
        totalFramesRead += framesRead;
    }
    return totalFramesRead;
}