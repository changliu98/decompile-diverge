int stbhw__weighted(int count, int *weights) {
    int sum = 0;
    int i;
    int r;
    int acc;

    // First loop: Calculate the sum of all weights
    for (i = 0; i < count; i++) {
        sum += weights[i];
    }

    // Generate a random number and scale it down
    // (Note: `rand()` is used here as a placeholder for the unlinked `call` at 0x48)
    r = (rand() >> 4) % sum;

    // Second loop: Find the index where the cumulative weight exceeds r
    acc = 0;
    for (i = 0; i < count; i++) {
        acc += weights[i];
        if (r < acc) {
            break;
        }
    }

    // Assert that a valid index was found
    // (Note: The exact assert message is missing due to stripped RIP-relative addresses)
    assert(i < count);

    return i;
}