double __cdecl rnd(int32_t *prandom) 
{
    // Update the seed using the LCG formula: Xn+1 = (a * Xn + c) mod m
    // Constants: a = 25173, c = 13849, m = 2^16 (0x10000)
    *prandom = (25173 * *prandom + 13849) % 0x10000;
    
    // Normalize the 16-bit integer (0 to 65535) to a double in [0.0, 1.0]
    // Note: The intermediate cast to (int) ensures signed division behavior 
    // if the seed ever exceeds 0x7FFF, though modulo 0x10000 limits it to 16 bits.
    return (double)(int)*prandom / 65535.0;
}