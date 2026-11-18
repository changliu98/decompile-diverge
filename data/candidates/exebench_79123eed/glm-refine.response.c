void __cdecl quant_u_dec(int index, float *p_data, float qmin, float qmax, int nlev)
{
    // Calculate the step size between quantization levels
    float step = (qmax - qmin) / (float)(nlev - 1);
    
    // Dequantize the index back into a floating-point value
    *p_data = (float)index * step + qmin;
}