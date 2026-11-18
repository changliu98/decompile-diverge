int __cdecl func0(int n)
{
    if (n == 1)
        return 1;
    
    // Computes 2^(n - 2) using bitwise left shift for integer powers of 2.
    // Note: The original floating-point `pow(2.0, ...)` implicitly truncates 
    // the result to an integer, which behaves identically to a bit shift for 
    // positive exponents. For negative exponents (n < 2), `pow` yields a 
    // fraction < 1.0, which truncates to 0, matching the behavior of the shift.
    return 1 << (n - 2);
}