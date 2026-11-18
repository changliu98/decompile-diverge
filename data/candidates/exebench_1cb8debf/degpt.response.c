/**
 * @brief Performs bitwise XOR on two floating-point inputs after casting them to integers.
 * 
 * @param bIn0 First input value (float).
 * @param bIn1 Second input value (float).
 * @param bOut Pointer to store the result (float).
 */
void sBitwiseXor_process(float input_a, float input_b, float *output_ptr)
{
    // Cast inputs to integers, perform bitwise XOR, then cast result back to float
    *output_ptr = (float)((int)input_a ^ (int)input_b);
}