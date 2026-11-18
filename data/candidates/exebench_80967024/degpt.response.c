/**
 * @brief Calculates the output signal length after upsampling with a filter.
 *
 * @param sigInLength       Input signal length.
 * @param filterLen         Length of the filter.
 * @param stride            Number of upsampling iterations.
 * @param sigOutLength      Pointer to store the calculated output length (with -2 adjustment).
 * @param sigOutLengthDefault Pointer to store the default output length (with -1 adjustment).
 */
void upcoef_len_cal(int inputSignalLength, int filterLength, int upsamplingIterations, int *adjustedOutputLength, int *defaultOutputLength)
{
    // Initialize both output lengths to the input signal length
    *adjustedOutputLength = inputSignalLength;
    *defaultOutputLength = inputSignalLength;
    
    // Perform 'stride' iterations of upsampling
    for (int iterationIndex = 0; iterationIndex < upsamplingIterations; iterationIndex++) {
        // Calculate default output length: double previous length and add filter length minus 1
        *defaultOutputLength = *defaultOutputLength * 2 + filterLength - 1;
        
        // Calculate adjusted output length: double previous length and add filter length minus 2
        *adjustedOutputLength = *adjustedOutputLength * 2 + filterLength - 2;
    }
}