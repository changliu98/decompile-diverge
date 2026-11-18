/**
 * Converts an array of double-precision floating-point samples to single-precision.
 *
 * @param pOut       Pointer to the output buffer for float samples.
 * @param pIn        Pointer to the input buffer for double samples.
 * @param sampleCount Number of samples to convert.
 */
void drwav_f64_to_f32(float *outputBuffer, double *inputBuffer, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        // Cast double to float and store in output buffer
        outputBuffer[i] = (float)inputBuffer[i];
    }
}