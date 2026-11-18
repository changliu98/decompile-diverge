int stb_div_eucl(int dividend, int divisor)
{
    int quotient, remainder;

    // Handle negative dividend cases to ensure Euclidean division properties
    if (dividend < 0) {
        // Special case: v1 is INT_MIN (-0x80000000)
        if (dividend == -0x80000000) {
            if (divisor < 0) {
                // Both v1 and v2 are negative
                if (divisor == -0x80000000) {
                    // Both are INT_MIN: quotient is 1, remainder is 0
                    quotient = 1;
                    remainder = 0;
                } else {
                    // v1 is INT_MIN, v2 is negative but not INT_MIN
                    // Compute quotient and remainder avoiding overflow
                    quotient = -(-0x80000000 - divisor) / -divisor + 1;
                    remainder = -(-(-0x80000000 - divisor) % -divisor);
                }
            } else {
                // v1 is INT_MIN, v2 is positive
                // Compute quotient and remainder avoiding overflow
                quotient = -1 - -(divisor + -0x80000000) / divisor;
                remainder = -(-(divisor + -0x80000000) % divisor);
            }
        } else if (divisor < 0) {
            // v1 is negative (but not INT_MIN), v2 is negative
            if (divisor == -0x80000000) {
                // v2 is INT_MIN: quotient is 1, remainder is v1 - INT_MIN
                quotient = 1;
                remainder = dividend + -0x80000000;
            } else {
                // Both negative, not INT_MIN: use negated values for standard division
                quotient = -dividend / -divisor;
                remainder = -(-dividend % -divisor);
            }
        } else {
            // v1 is negative (but not INT_MIN), v2 is positive
            // Use negated dividend for standard division
            quotient = -(-dividend / divisor);
            remainder = -(-dividend % divisor);
        }
    } else {
        // Handle non-negative dividend cases
        if (divisor > -1) {
            // v2 is positive: standard division suffices
            return dividend / divisor;
        }
        if (divisor == -0x80000000) {
            // v2 is INT_MIN: quotient is 0, remainder is v1
            quotient = 0;
            remainder = dividend;
        } else {
            // v1 is non-negative, v2 is negative (but not INT_MIN)
            // Use negated divisor for standard division
            quotient = -(dividend / -divisor);
            remainder = dividend % -divisor;
        }
    }

    // Adjust quotient and remainder to ensure Euclidean division property:
    // remainder has the same sign as the divisor (or is zero)
    if (remainder < 0) {
        quotient += (divisor > 0) ? -1 : 1;
    }

    return quotient;
}