drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav *pWav, drwav_uint64 framesToRead, drwav_int32 *pBufferOut)
{
    drwav_uint64 totalFramesRead = 0;
    unsigned char sampleData[4096];
    memset(sampleData, 0, sizeof(sampleData));

    unsigned int bytesPerSample;
    if ((drwav_uint32)(pWav->translatedFormatTag) == 0x1) {
        return 0;
    }

    unsigned int bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav) / pWav->channels;
    if (bytesPerFrame == 0 || (drwav_uint32)(pWav->translatedFormatTag) == 0x1) {
        return 0;
    }

    while (framesToRead > 0) {
        drwav_uint64 framesRead;
        drwav_uint64 samplesRead;
        size_t bytesRead;
        drwav_uint64 samplesToRead;

        drwav_uint64 framesToReadThisIteration;
        if (framesToRead < (sizeof(sampleData)/bytesPerFrame)) {
            framesToReadThisIteration = framesToRead;
        } else {
            framesToReadThisIteration = (sizeof(sampleData)/bytesPerFrame);
        }

        framesRead = drwav_read_pcm_frames(pWav, framesToReadThisIteration, sampleData);
        if (framesRead == 0) {
            break;
        }
        ((void)(framesRead <= framesToReadThisIteration));;

        samplesRead = framesRead * pWav->channels;
        ((void)(samplesRead <= (sizeof(sampleData)/bytesPerSample)));;

        drwav_mulaw_to_s32(pBufferOut, sampleData, samplesRead);

        pBufferOut += samplesRead;
        framesToRead -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}