void rational_best_approximation(
    uint64_t given_numerator, 
    uint64_t given_denominator,
    uint64_t max_numerator, 
    uint64_t max_denominator,
    uint64_t *best_numerator, 
    uint64_t *best_denominator
) {
    uint64_t a = given_numerator;
    uint64_t b = given_denominator;
    
    // Initialize convergents:
    // h0 = 0, k0 = 1 (previous convergent)
    // h1 = 1, k1 = 0 (current convergent)
    uint64_t h0 = 0, k0 = 1;
    uint64_t h1 = 1, k1 = 0;

    while (1) {
        // If the current convergent exceeds either of the maximum bounds
        if (k1 > max_denominator || h1 > max_numerator) {
            // Revert to the previous convergent
            h1 = h0;
            k1 = k0;
            break;
        }

        // If the denominator of the remaining fraction is 0, we are done
        if (b == 0) {
            break;
        }

        // Compute the next term in the continued fraction expansion
        uint64_t q = a / b;
        uint64_t rem = a % b;
        
        // Update a and b for the next iteration
        a = b;
        b = rem;

        // Compute the next convergent
        uint64_t h_next = h0 + q * h1;
        uint64_t k_next = k0 + q * k1;

        // Shift the convergents for the next iteration
        h0 = h1;
        k0 = k1;
        h1 = h_next;
        k1 = k_next;
    }

    // Store the best approximation results via output pointers
    *best_numerator = h1;
    *best_denominator = k1;
}