void multiply(int a, int b, int *result) {
    // Calculate the product and mask it to keep only the lower 31 bits
    int masked_product = (a * b) & 0x7fffffff;
    result[0] = masked_product;
    
    // Calculate the exact product as a double
    double exact_product = (double)a * (double)b;
    double adjusted_product;
    
    // Adjust the product based on the value of the masked product
    if (masked_product < 0x40000000) {
        // Add 1.0 and divide by 2.0
        adjusted_product = (exact_product + 1.0) / 2.0;
    } else {
        // Subtract 1.0 and divide by 2.0
        adjusted_product = (exact_product - 1.0) / 2.0;
    }
    
    // Store the truncated integer result
    result[1] = (int)adjusted_product;
}