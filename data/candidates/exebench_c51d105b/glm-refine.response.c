void __cdecl png_64bit_product(long v1, long v2, unsigned __int64 *hi_product, unsigned __int64 *lo_product)
{
    // Cast the 32-bit inputs to 64-bit unsigned integers to prevent overflow
    unsigned __int64 a = (unsigned __int64)(unsigned __int32)v1;
    unsigned __int64 b = (unsigned __int64)(unsigned __int32)v2;

    // Compute the full 128-bit product
    unsigned __int64 lo = a * b;
    
    // The high 64 bits of the product can be extracted by right-shifting 
    // the 128-bit result by 64 bits. In C, this is mathematically equivalent 
    // to the sum of the cross-products of the 16-bit limbs.
    unsigned __int64 hi = lo >> 32;

    // Assign the results to the output pointers
    if (hi_product) {
        *hi_product = hi;
    }
    if (lo_product) {
        *lo_product = lo;
    }
}