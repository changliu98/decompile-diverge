int func0(int *A, int N) {
    int oddXorPairCount = 0; // Initialize counter for pairs with odd XOR sum
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Check if XOR of A[i] and A[j] is odd
            if ((A[i] ^ A[j]) % 2 != 0) {
                oddXorPairCount++; // Increment counter if XOR result is odd
            }
        }
    }
    return oddXorPairCount; // Return total count of pairs with odd XOR sum
}