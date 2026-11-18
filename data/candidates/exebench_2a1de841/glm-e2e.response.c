double linsched_rand(unsigned int *state) {
    unsigned int next = *state * 0x41a7;
    
    // The compiler optimized the modulo operation `next % 0x7fffffff` 
    // using a sequence of multiplication, shifts, and subtractions.
    next = next % 0x7fffffff;
    
    *state = next;
    
    return (double)next / 2147483647.0;
}