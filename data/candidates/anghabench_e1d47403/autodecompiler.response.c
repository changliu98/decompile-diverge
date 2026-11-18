unsigned int mul_poly(unsigned int multiplicand, unsigned int multiplier, unsigned int divisor)
{
    unsigned int product = 0;
    while(1) {
        if(multiplicand & 1) product ^= multiplier;
        multiplicand >>= 1;
        multiplier <<= 1;
        if(multiplier & 0x10000) multiplier ^= divisor;
        if(multiplicand == 0) break;
    }
    return product;
}