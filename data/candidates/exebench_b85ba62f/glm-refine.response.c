unsigned __int64 __cdecl rational_best_approximation(
        unsigned __int64 given_numerator,
        unsigned __int64 given_denominator,
        unsigned __int64 max_numerator,
        unsigned __int64 max_denominator,
        unsigned __int64 *best_numerator,
        unsigned __int64 *best_denominator)
{
    // Convergents initialization:
    // n0/d0 represents the previous convergent (initially 0/1)
    // n1/d1 represents the current convergent (initially 1/0)
    unsigned __int64 n0 = 0, d0 = 1;
    unsigned __int64 n1 = 1, d1 = 0;

    // The loop computes the continued fraction expansion of given_numerator/given_denominator.
    // It stops when the convergent exceeds the specified maximum numerator or denominator.
    while (n1 <= max_numerator && d1 <= max_denominator)
    {
        if (!given_denominator)
            break;

        // Compute the next term 'a' of the continued fraction
        unsigned __int64 a = given_numerator / given_denominator;
        unsigned __int64 t = given_denominator;
        
        // Update the fraction for the next iteration
        given_denominator = given_numerator % given_denominator;
        given_numerator = t;

        // Compute the next convergent
        unsigned __int64 ta = n1 * a + n0;
        unsigned __int64 tb = d1 * a + d0;

        // Shift convergents for the next iteration
        n0 = n1;
        n1 = ta;
        d0 = d1;
        d1 = tb;
    }

    // If the loop terminated because the current convergent (n1/d1) exceeded the bounds,
    // revert to the previous valid convergent (n0/d0).
    n1 = n0;
    d1 = d0;

    *best_numerator = n1;
    *best_denominator = d1;
    
    return 0;
}