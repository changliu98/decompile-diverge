int decToBin(unsigned int n, int *arr) {
    unsigned int power = 1;
    int count = 0;
    int i;

    // Find the smallest power of 2 strictly greater than n
    while (power <= n) {
        power <<= 1;
        count++;
    }

    // Step back to the highest power of 2 less than or equal to n
    power >>= 1;
    count--;

    // Store the number of bits in the array
    i = count;

    // Convert decimal to binary
    while (i >= 0) {
        if ((int)(n - power) >= 0) {
            n -= power;
            arr[count - i] = 1;
        } else {
            arr[count - i] = 0;
        }
        power >>= 1;
        i--;
    }

    return count;
}