/**
 * Converts an array of double-precision floating-point samples to 32-bit signed integers.
 *
 * @param pOut       Pointer to the output buffer for the converted 32-bit signed integer samples.
 * @param pIn        Pointer to the input buffer containing double-precision floating-point samples.
 * @param sampleCount The number of samples to convert.
 */
void drwav_f64_to_s32(drwav_int32 *outputBuffer, double *inputBuffer, size_t numSamples)
{
    for (size_t index = 0; index < numSamples; index++) {
        // Convert double to int by multiplying with a scaling factor and casting to 32-bit integer
        outputBuffer[index] = (int)(scalingFactor * inputBuffer[index]);
    }
}