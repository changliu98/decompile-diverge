void Sqrt(float x, float *out) {
    // Step 1: Initial approximation using the fast inverse square root magic constant
    float x_half = x * 0.5f;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    float y = *(float*)&i;
    
    // Step 2: One iteration of Newton-Raphson refinement to improve accuracy
    y = y * (1.5f - (x_half * y * y));
    
    // Step 3: Calculate the square root by taking the reciprocal of the inverse square root
    float result = 1.0f / y;
    
    // Step 4: Check if the result is a valid positive number
    // If x was negative, y would be NaN, and result would also be NaN.
    // The ucomiss and jbe check if result > 0.0f (handling NaN by failing the condition)
    if (result > 0.0f) {
        *out = result;
    } else {
        *out = 0.0f;
    }
}