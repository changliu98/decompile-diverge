void drwav_s32_to_f32(float *outputBuffer, drwav_int32 *inputBuffer, size_t numSamples)
{
    // Iterate through each sample to convert signed 32-bit integers to floating-point values
    for (size_t index = 0; index < numSamples; index++) {
        // Convert the integer sample to double, divide by the maximum positive value of a 32-bit signed integer (2^31),
        // and cast the result to float to normalize the range to [-1.0, 1.0)
        outputBuffer[index] = (float)((double)inputBuffer[index] / MAX_INT32_PLUS_ONE);
    }
}