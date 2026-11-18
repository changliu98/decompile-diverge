int func0(int n) {
    int count = 0;
    int result;

    if (n != 0 && (n & (n - 1)) == 0) {
        /* n is already a power of 2 */
        result = n;
    } else {
        /* Count bits needed to represent n */
        while (n != 0) {
            n >>= 1;
            count++;
        }
        result = 1 << count;
    }

    return result;
}