int __cdecl gcd_ptr(int *u, int *v)
{
    int *t;

    // Loop until the value pointed to by 'u' is zero
    while (*u > 0)
    {
        // Ensure *u >= *v by swapping pointers if necessary
        if (*u < *v)
        {
            t = u;
            u = v;
            v = t;
        }
        
        // Subtract the smaller value from the larger value
        *u -= *v;
    }
    
    // Once *u reaches 0, *v contains the Greatest Common Divisor (GCD)
    return *v;
}