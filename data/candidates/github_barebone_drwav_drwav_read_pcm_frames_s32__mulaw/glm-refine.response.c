drwav_uint64 __cdecl drwav_read_pcm_frames_s32__mulaw(drwav *pWav, drwav_uint64 framesToRead, drwav_int32 *pBufferOut)
{
    drwav_uint64 framesToReadThisIteration;
    drwav_uint64 framesRead;
    drwav_uint64 samplesRead;
    drwav_uint32 bytesPerSample;
    drwav_uint32 bytesPerFrame;
    drwav_uint8 sampleData[4096];
    drwav_uint64 totalFramesRead = 0;

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (!bytesPerFrame)
        return 0;

    bytesPerSample = bytesPerFrame / pWav->channels;
    if (!bytesPerSample || bytesPerFrame % pWav->channels)
        return 0;

    while (framesToRead > 0)
    {
        // Read in chunks of up to 4096 bytes
        framesToReadThisIteration = (framesToRead >= 4096 / bytesPerFrame) ? 4096 / bytesPerFrame : framesToRead;
        
        framesRead = drwav_read_pcm_frames(pWav, framesToReadThisIteration, sampleData);
        if (!framesRead)
            break;

        assert(framesRead <= framesToReadThisIteration);

        samplesRead = pWav->channels * framesRead;
        
        assert(bytesPerSample * samplesRead <= 4096);

        drwav_mulaw_to_s32(pBufferOut, sampleData, samplesRead);
        
        pBufferOut += samplesRead;
        framesToRead -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}