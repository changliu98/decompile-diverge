// Converts an array of 32-bit floating-point samples to signed 32-bit integer samples.
//
// Parameters:
//   pOut       - Pointer to the output buffer for the resulting int32 samples.
//   pIn        - Pointer to the input buffer containing the float samples.
//   sampleCount - The number of samples to convert.
//
// Note: The conversion uses a hardcoded scaling factor (DAT_00114098) to map
//       the float range to the int32 range. This appears to be a decompiled
//       constant representing the maximum int32 value (2147483647.0f).
void drwav_f32_to_s32(drwav_int32 *outputBuffer, float *inputBuffer, size_t numSamples)
{
    for (size_t index = 0; index < numSamples; index++) {
        // Cast the scaled float result to int32.
        // This truncates the fractional part.
        outputBuffer[index] = (int)(MAX_INT32_FLOAT * inputBuffer[index]);
    }
}