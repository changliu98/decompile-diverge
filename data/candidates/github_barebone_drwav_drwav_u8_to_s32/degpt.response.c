void drwav_u8_to_s32(drwav_int32 *outputBuffer, drwav_uint8 *inputBuffer, size_t numSamples)
{
    size_t index;
    // Validate input pointers before processing
    if (outputBuffer && inputBuffer) {
        for (index = 0; index < numSamples; index++) {
            // Convert 8-bit unsigned PCM to 32-bit signed PCM
            // Subtract 0x80 to shift range from [0, 255] to [-128, 127]
            // Multiply by 0x1000000 to scale to 32-bit integer range
            outputBuffer[index] = (inputBuffer[index] - 0x80) * 0x1000000;
        }
    }
}