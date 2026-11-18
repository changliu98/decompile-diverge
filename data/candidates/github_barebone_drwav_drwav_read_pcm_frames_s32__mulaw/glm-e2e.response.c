The decompiled function
size_t drwav_read_pcm_frames_s32__mulaw(drwav *pWav, size_t framesToRead, int32_t *pBufferOut) {
    size_t framesRead = 0;
    uint8_t sampleData[4096];

    drwav__malloc_default(0); // Likely an artifact from inlined drwav__malloc_from_callbacks
    uint32_t bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);

    if (bytesPerFrame == 0) {
        return 0;
    }

    // Check if bytesPerFrame is a multiple of channels
    if (bytesPerFrame / pWav->channels == 0 || bytesPerFrame % pWav->channels != 0) {
        return 0;
    }

    while (framesToRead > 0) {
        size_t framesToReadThisIteration;
        
        // Limit the number of frames read to fit inside the 4096-byte stack buffer
        if (framesToRead < 4096 / bytesPerFrame) {
            framesToReadThisIteration = framesToRead;
        } else {
            framesToReadThisIteration = 4096 / bytesPerFrame;
        }

        size_t framesReadThisIteration = drwav_read_raw(pWav, framesToReadThisIteration, sampleData);
        if (framesReadThisIteration == 0) {
            break;
        }

        // Assert that we didn't read more than requested
        drwav__assert(framesReadThisIteration <= framesToReadThisIteration, "framesReadThisIteration <= framesToReadThisIteration", "dr_wav.c", 0x1f0a);

        size_t bytesToConvert = framesReadThisIteration * pWav->channels;
        
        // Assert that the number of bytes to convert doesn't exceed the buffer size
        drwav__assert(bytesToConvert * (bytesPerFrame / pWav->channels) <= 4096, "bytesToConvert * (bytesPerFrame / pWav->channels) <= sizeof(sampleData)", "dr_wav.c", 0x1f0f);

        // Convert the raw mu-law data to 32-bit signed integers
        drwav_mulaw_to_s32(pBufferOut, sampleData, bytesToConvert);

        // Advance the output buffer pointer
        pBufferOut += bytesToConvert;

        // Update the remaining frames to read and total frames read
        framesToRead -= framesReadThisIteration;
        framesRead += framesReadThisIteration;
    }

    return framesRead;
}