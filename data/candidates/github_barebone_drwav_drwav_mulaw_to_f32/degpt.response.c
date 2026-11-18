// Converts an array of mu-law encoded samples to 32-bit floating-point values.
// pOut: Pointer to the output buffer where converted float samples will be stored.
// pIn: Pointer to the input buffer containing mu-law encoded unsigned char samples.
// sampleCount: The number of samples to convert.
void drwav_mulaw_to_f32(float *outputBuffer, drwav_uint8 *inputBuffer, size_t numSamples)
{
    // Iterate through each sample in the input buffer.
    for (size_t index = 0; index < numSamples; index++) {
        // Look up the linear PCM value in the mu-law decoding table,
        // cast it to a short, then to an int, and finally convert to float.
        // Divide by the scaling factor to normalize the sample to the [-1.0, 1.0] range.
        outputBuffer[index] = (float)(int)(short)g_drwavMulawTable[inputBuffer[index]] / MULAW_SCALING_FACTOR;
    }
}