void drwav_alaw_to_s32(drwav_int32 *outputBuffer, drwav_uint8 *inputBuffer, size_t numSamples)
{
    // Iterate through each sample to convert from A-law to 32-bit signed integer
    for (size_t index = 0; index < numSamples; index++) {
        // Look up the 16-bit signed value in the A-law conversion table,
        // then sign-extend it to 32-bit by shifting left by 16 bits.
        outputBuffer[index] = (int)(short)g_drwavAlawTable[inputBuffer[index]] << 0x10;
    }
}