drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerSample;
    drwav_uint32 bytesPerFrame;

    memset((sampleData), 0, (sizeof(sampleData)));

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    bytesPerSample = bytesPerFrame / pWav->channels;
    if (bytesPerSample == 0 || bytesPerFrame % pWav->channels) {
        return 0;
    }

    totalFramesRead = 0;

    for (;;)
    {
        drwav_uint64 framesRead;
        drwav_uint64 framesToReadThisIteration;
        drwav_uint64 sampleCount;

        framesToReadThisIteration = framesToRead;
        if (framesToReadThisIteration > (sizeof(sampleData) / bytesPerFrame)) {
            framesToReadThisIteration = (sizeof(sampleData) / bytesPerFrame);
        }

        framesRead = drwav_read_pcm_frames(pWav, framesToReadThisIteration, sampleData);
        if (framesRead == 0) {
            break;
        }

        ((framesRead <= framesToReadThisIteration) ? (void)0 : __assert_fail("framesRead <= framesToReadThisIteration", "func.c", 7946, "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"));

        sampleCount = framesRead*pWav->channels;
        ((sampleCount*bytesPerSample <= sizeof(sampleData)) ? (void)0 : __assert_fail("0", "func.c", 7951, "drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *, drwav_uint64, drwav_int32 *)"));

        drwav_mulaw_to_s32(pBufferOut, sampleData, (size_t)sampleCount);

        pBufferOut += sampleCount;
        totalFramesRead += framesRead;
        framesToRead -= framesRead;

        if (framesToRead == 0) {
            break;
        }
    }

    return totalFramesRead;
}