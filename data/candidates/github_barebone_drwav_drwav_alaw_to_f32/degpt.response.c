// Converts A-law encoded audio samples to 32-bit floating-point format.
//
// Parameters:
//   pOut      - Pointer to the output buffer where converted float samples will be stored.
//   pIn       - Pointer to the input buffer containing A-law encoded unsigned char samples.
//   sampleCount - The number of samples to convert.
//
// Process:
//   1. Each input byte (A-law encoded) is used as an index into g_drwavAlawTable.
//   2. The table lookup returns a 16-bit signed integer representing the linear PCM value.
//   3. The 16-bit integer is cast to a float.
//   4. The float value is divided by DAT_00114094 (likely a normalization constant, e.g., 32768.0)
//      to scale the result into the range [-1.0, 1.0].
void drwav_alaw_to_f32(float *outputBuffer, drwav_uint8 *inputBuffer, size_t numSamples)
{
    for (size_t index = 0; index < numSamples; index++) {
        // Lookup linear PCM value from A-law table, cast to short, then to float, and normalize.
        outputBuffer[index] = (float)(int)(short)alawConversionTable[inputBuffer[index]] / normalizationConstant;
    }
}