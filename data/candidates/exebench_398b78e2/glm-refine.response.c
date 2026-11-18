float __cdecl reson(float x, float *a)
{
    // The XOR operation flips the sign bit of the float.
    float neg_a2 = -a[2]; 
    
    // Calculate the new state (y[n] = b0*x[n] + a1*y[n-1] - a2*y[n-2])
    float temp = (a[0] * x) + (a[1] * a[3]) + (neg_a2 * a[4]);
    
    // Shift the state history
    a[4] = a[3];
    a[3] = temp;
    
    return temp;
}