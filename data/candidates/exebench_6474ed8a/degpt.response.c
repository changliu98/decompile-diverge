// Generates a Galois Field (GF(2^8)) multiplication table for a given primitive polynomial.
// dst: Output buffer to store the generated table (must be at least 256 bytes).
// prim_poly: The primitive polynomial used for the field arithmetic (must have bit 8 set).
// Returns 0 on success, -1 if the primitive polynomial is invalid.
int gen256(uchar *table, uint primitive_polynomial)
{
    // Validate that the primitive polynomial has the x^8 term (bit 8 must be set).
    if ((primitive_polynomial & 0x100) == 0) {
        return -1;
    }
    // Initialize the first two elements of the table: 0 and 1.
    table[0] = '\0';
    table[1] = '\x01';
    uint current_value = 1;
    // Compute subsequent powers of x in the Galois Field.
    for (int index = 2; index < 0x100; index++) {
        // Multiply by x (left shift).
        current_value = current_value << 1;
        // If overflow occurs (bit 8 is set), reduce modulo the primitive polynomial.
        if (current_value & 0x100) {
            current_value = (primitive_polynomial & 0xff) ^ (current_value & 0xff);
        }
        // Store the result in the table.
        table[index] = (uchar)current_value;
    }
    return 0;
}