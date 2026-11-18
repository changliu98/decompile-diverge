void increment(int *p) {
    int val = *p;
    int mask = 1;
    
    // Flip all trailing 1s to 0s, and the first 0 to 1
    while (val & mask) {
        val ^= mask;
        mask <<= 1;
    }
    
    // Set the first 0 bit (which stopped the loop) to 1
    val ^= mask;
    
    *p = val;
}