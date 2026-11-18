float __cdecl getUniform(int a, int c, int m, float *x)
{
    // Step 1: Compute the next state of the Linear Congruential Generator (LCG)
    float next_val = (a * (*x)) + c;
    
    // Step 2: Cast to integer to apply the modulo arithmetic (floor behavior for positive numbers)
    int truncated = (int)(next_val / m);
    
    // Step 3: Calculate the remainder (next_val % m) and normalize to [0.0, 1.0)
    *x = (next_val - (m * truncated)) / m;
    
    return *x;
}