// Computes Galois Field multiplication of a and b modulo p (GF(2^8))
// where p is an irreducible polynomial of degree 8.
// Input: a, b are bytes (8-bit values), p is the irreducible polynomial.
// Output: result of (a * b) mod p in GF(2^8).
ulong32 gf_mult(ulong32 multiplicand, ulong32 multiplicand_value, ulong32 irreducible_polynomial)
{
    ulong32 polynomial_table[2]; // Array to store polynomial values for doubling
    ulong32 result_accumulator[2]; // Array to accumulate the result based on bits of a
    ulong32 loop_index;

    // Initialize P[1] with the irreducible polynomial p
    // P[0] will be used to store the result of doubling when overflow occurs
    polynomial_table[1] = irreducible_polynomial;
    
    // Initialize B[1] with the multiplicand b
    // B[0] is initialized to 0 (accumulated result for the case when MSB is 0)
    result_accumulator[1] = multiplicand_value;
    result_accumulator[0] = 0;
    
    // P[0] is initialized to 0; it will hold the doubled value of P[1] if needed
    polynomial_table[0] = 0;

    // Perform 7 iterations of doubling B[1] in GF(2^8)
    // Each iteration computes B[1] = 2 * B[1] mod p
    // The expression (B[1] >> 7) checks if the MSB was set before shifting
    // If MSB was set, XOR with p (stored in P[1]) to reduce modulo p
    // Otherwise, XOR with P[0] (which is 0, so no change)
    for (loop_index = 0; loop_index < 7; loop_index++) {
        result_accumulator[1] = polynomial_table[result_accumulator[1] >> 7] ^ (result_accumulator[1] << 1);
    }

    // Compute the final result by combining precomputed values based on bits of a
    // This effectively performs the multiplication using the Russian Peasant algorithm
    // or a lookup-based approach where B[0] and B[1] hold intermediate results
    // for the current bit position of a.
    // The result is the XOR sum of B[a_i] for each bit a_i of a.
    return result_accumulator[multiplicand >> 7 & 1] ^
           result_accumulator[multiplicand >> 6 & 1] ^
           result_accumulator[multiplicand >> 5 & 1] ^ result_accumulator[multiplicand >> 4 & 1] ^ result_accumulator[multiplicand >> 3 & 1] ^ result_accumulator[multiplicand >> 2 & 1] ^ result_accumulator[multiplicand >> 1 & 1] ^ result_accumulator[multiplicand & 1];
}