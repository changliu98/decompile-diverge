int ok_smul4(int multiplier_a, int multiplier_b, int *result_pointer) {
    // Multiply x and y, storing the result in the memory location pointed to by dest
    *result_pointer = multiplier_a * multiplier_b;
    // Return 1 to indicate success
    return 1;
}