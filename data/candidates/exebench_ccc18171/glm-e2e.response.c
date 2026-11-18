bool ok_smul4(int32_t a, int32_t b, int32_t* out) {
    *out = a * b;
    // setae sets the result to 1 if the carry flag (CF) is clear, 0 otherwise.
    // For signed multiplication (imul), CF is cleared if no overflow occurred.
    return !__builtin_overflow(a * b); 
}