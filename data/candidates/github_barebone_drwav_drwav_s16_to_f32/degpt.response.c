void drwav_s16_to_f32(float *outputBuffer, drwav_int16 *inputBuffer, size_t numSamples)
{
    // Iterate through each sample in the input buffer
    for (size_t index = 0; index < numSamples; index++) {
        // Convert 16-bit signed integer to float and scale to [-1.0, 1.0] range
        outputBuffer[index] = (float)(int)inputBuffer[index] * DAT_00114090;
    }
}