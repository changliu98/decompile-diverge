void shr(struct uint128_t *num, int shift) {
    if (shift >= 64) {
        shift -= 64;
        num->low = num->high;
        num->high = 0;
    }
    
    num->low = (num->low >> shift) | (num->high << (64 - shift));
    num->high = num->high >> shift;
}