// Function renamed to reflect its true semantic behavior
bool __cdecl is_not_positive_odd(int n)
{
    // In C/C++, the modulo operator (%) retains the sign of the dividend.
    // Therefore, for negative odd numbers, n % 2 evaluates to -1, not 1.
    // This means the original condition (n % 2 != 1) is only false for positive odd numbers.
    // 
    // Semantically, this is equivalent to: n is non-positive OR n is even.
    return n <= 0 || n % 2 == 0;
}