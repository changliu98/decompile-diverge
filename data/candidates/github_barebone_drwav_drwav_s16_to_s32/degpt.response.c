// Converts an array of 16-bit signed integers to 32-bit signed integers.
// Each 16-bit sample is sign-extended to 32 bits by shifting left by 16 bits.
//
// Parameters:
//   pOut       - Pointer to the output array of 32-bit signed integers.
//   pIn        - Pointer to the input array of 16-bit signed integers.
//   sampleCount - Number of samples to convert.
void drwav_s16_to_s32(drwav_int32 *outputBuffer, drwav_int16 *inputBuffer, size_t numSamples)
{
    size_t index;
    // Check for null pointers to prevent dereferencing invalid memory.
    if ((outputBuffer != (drwav_int32 *)0x0) && (inputBuffer != (drwav_int16 *)0x0)) {
        // Iterate through each sample and convert from s16 to s32.
        for (index = 0; index < numSamples; index = index + 1) {
            // Cast to int to ensure proper sign extension, then shift left by 16 bits.
            // This effectively multiplies the 16-bit value by 2^16, preserving the sign.
            outputBuffer[index] = (int)inputBuffer[index] << 0x10;
        }
    }
    return;
}