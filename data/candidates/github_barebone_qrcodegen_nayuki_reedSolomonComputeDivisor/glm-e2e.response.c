void reedSolomonComputeDivisor(int degree, uint8_t *result) {
    // Assert that degree is between 1 and 30
    assert(degree >= 1 && degree <= 30);

    // Initialize the result array to 0
    memset(result, 0, degree);

    // Set the highest-order coefficient to 1
    result[degree - 1] = 1;

    uint8_t root = 1;

    // Outer loop: compute the polynomial product (x - root^i) for i = 0 to degree - 1
    for (int i = 0; i < degree; i++) {
        // Inner loop: multiply the current polynomial by (x - root)
        for (int j = 0; j < degree; j++) {
            result[j] = gfMultiply(result[j], root);
            
            // If not the last element, add (XOR in GF(2^8)) the next coefficient
            if (j + 1 < degree) {
                result[j] ^= result[j + 1];
            }
        }
        // Update the root for the next iteration: root = 2^i in GF(256)
        root = gfPow2(i);
    }
}