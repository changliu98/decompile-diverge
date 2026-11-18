int clk_div_even_up(int divisor) {
    int result;
    
    if (divisor == 1) {
        result = 1;
    } else {
        // The bitwise AND with 0xFFFFFFFE clears the least significant bit,
        // effectively rounding down to the nearest even number.
        // Adding 1 before the AND rounds up to the next even number if it's odd.
        result = (divisor + 1) & 0xFFFFFFFE;
    }
    
    return result;
}