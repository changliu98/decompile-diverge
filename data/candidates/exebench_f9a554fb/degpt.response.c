// Performs Maximal Ratio Combining (MRC) on Log-Likelihood Ratios (LLRs) for relay processing.
// Accumulates quantized LLR values into the sum array.
//
// Parameters:
//   llr_quant       : Pointer to the input array of quantized LLR values.
//   arraySize       : Number of elements in the LLR arrays.
//   llr_quant_sum   : Pointer to the output array where LLR values are accumulated.
void dlsch_MRC_relay_LLR(short *llr_values, uint num_elements, short *accumulated_llrs)
{
    // Iterate through each element of the LLR array
    for (uint i = 0; i < num_elements; i++) {
        // Accumulate the current LLR value into the sum array
        accumulated_llrs[i] += llr_values[i];
    }
}