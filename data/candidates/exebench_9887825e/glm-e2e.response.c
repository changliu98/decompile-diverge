int _safe_calloc_check_mul(uint64_t arg1, uint64_t arg2, uint64_t *arg3) {
    uint64_t a = arg1;
    uint64_t b = arg2;
    uint64_t local_res;
    uint64_t *res_ptr;

    if (arg3 != NULL) {
        res_ptr = arg3;
    } else {
        res_ptr = &local_res;
    }

    uint64_t result = a * b;
    *res_ptr = result;

    // The 'mul' instruction sets the Carry Flag (CF) and Overflow Flag (OF) 
    // if the upper half of the result is non-zero.
    // 'seto %al' sets %al to 1 if OF is 1 (overflow occurred).
    // 'xor $0xff, %al' flips the bits, so 1 becomes 0xFE, and 0 becomes 0xFF.
    // 'and $0x1, %al' isolates the lowest bit, resulting in 0 if overflow occurred, and 1 otherwise.
    int no_overflow = !__builtin_mul_overflow(a, b, res_ptr);

    return no_overflow;
}