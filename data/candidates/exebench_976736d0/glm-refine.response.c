unsigned __int64 __cdecl div10quickm(unsigned __int64 *tp)
{
    unsigned __int64 t = *tp;
    
    // Step 1: Calculate t * 0.10009765625 (approximation of t / 10)
    // This is done using a sequence of right shifts and additions.
    unsigned __int64 s1 = (t >> 1) + (t >> 2);
    unsigned __int64 s2 = s1 + (s1 >> 4);
    unsigned __int64 s3 = s2 + (s2 >> 8);
    unsigned __int64 s4 = s3 + (s3 >> 16);
    unsigned __int64 q_approx = s4 >> 3;
    
    // Step 2: Correct the approximation error to get the exact floor division
    // The error is bounded, so we subtract 10 * q_approx from t, shift right by 9, 
    // and add it back to q_approx to get the exact quotient.
    unsigned __int64 q = q_approx + ((t - 10 * q_approx) >> 9);
    
    // Step 3: Store the exact quotient and return the remainder (t - 10 * q)
    *tp = q;
    return t - 10 * q;
}