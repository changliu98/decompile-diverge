DRWAV_PRIVATE drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096] = {0};
    drwav_uint32 bytesPerFrame;
    drwav_uint32 bytesPerSample;
    drwav_uint64 samplesRead;

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    bytesPerSample = bytesPerFrame / pWav->channels;
    if (bytesPerSample == 0 || (bytesPerFrame % pWav->channels) != 0) {
        return 0;   /* Only byte-aligned formats are supported. */
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesToReadThisIteration = drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame);
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, framesToReadThisIteration, sampleData);
        if (framesRead == 0) {
            break;
        }

        DRWAV_ASSERT(framesRead <= framesToReadThisIteration);   /* If this fails it means there's a bug in drwav_read_pcm_frames(). */

        /* Validation to ensure we don't read too much from out intermediary buffer. This is to protect from invalid files. */
        samplesRead = framesRead * pWav->channels;
        if ((samplesRead * bytesPerSample) > sizeof(sampleData)) {
            DRWAV_ASSERT(DRWAV_FALSE);  /* This should never happen with a valid file. */
            break;
        }

        drwav_mulaw_to_s32(pBufferOut, sampleData, (size_t)samplesRead);

        #ifdef DR_WAV_LIBSNDFILE_COMPAT
        {
            if (pWav->container == drwav_container_aiff) {
                drwav_uint64 iSample;
                for (iSample = 0; iSample < samplesRead; iSample += 1) {
                    pBufferOut[iSample] = -pBufferOut[iSample];
                }
            }
        }
        #endif

        pBufferOut      += samplesRead;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}