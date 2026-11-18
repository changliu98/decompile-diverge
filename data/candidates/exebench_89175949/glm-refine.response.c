int32_t __cdecl foo(int32_t *a, int32_t *b, int32_t c)
{
    // Multiply *a by 2
    *a *= 2;

    // Divide *b by 2. 
    // Note: Compilers typically optimize '/ 2' into a right-shift 
    // (e.g., (*b - (*b >> 31)) >> 1) to handle signed integer rounding correctly.
    *b = (int32_t)((uint32_t)*b / 2);

    // Return the sum of the modified values
    return *b + *a;
}