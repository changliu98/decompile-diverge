void drwav_mulaw_to_s32(drwav_int32 *outputBuffer, drwav_uint8 *inputBuffer, size_t numSamples)
{
    // Iterate through each sample in the input buffer
    for (size_t index = 0; index < numSamples; index++) {
        // Convert mu-law encoded byte to 16-bit PCM value using lookup table,
        // then sign-extend and shift to 32-bit signed integer format
        outputBuffer[index] = (int)(short)g_drwavMulawTable[inputBuffer[index]] << 0x10;
    }
}