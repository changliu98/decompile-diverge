void gf2field_mul(uint32_t *result, uint32_t *operand_a, uint32_t *operand_b)
{
    gf2elem_t accumulator;
    int bit_index;

    // Copy x into temporary variable tmp
    bitvec_copy(accumulator, operand_a);
    // Initialize result z to zero
    bitvec_set_zero(result);

    // If the least significant bit of y is set, initialize result with x
    if (bitvec_get_bit(operand_b, 0)) {
        bitvec_copy(result, operand_a);
    }

    // Iterate through remaining bits of y up to degree 0xa3 (163)
    for (bit_index = 1; bit_index < 0xa3; bit_index++) {
        // Left shift tmp by 1 (multiply by x)
        bitvec_lshift(accumulator, accumulator, 1);
        // If overflow occurs at bit 0xa3, reduce modulo the irreducible polynomial
        if (bitvec_get_bit(accumulator, 0xa3)) {
            gf2field_add(accumulator, accumulator, irreducible_poly);
        }
        // If the i-th bit of y is set, add the current shifted value to the result
        if (bitvec_get_bit(operand_b, bit_index)) {
            gf2field_add(result, result, accumulator);
        }
    }
}