// Converts the 4 least significant bits of the input integer _src into individual bit values
// and stores them in the dstBits array.
// Each element dstBits[i] contains the i-th bit of _src (0 or 1).
void yxyDES2_Int2Bits(uint sourceValue, char *bitArray)
{
    // Iterate over the 4 least significant bits
    for (uint bitIndex = 0; bitIndex < 4; bitIndex++) {
        // Extract the i-th bit:
        // 1. Shift _src left by i positions to move the i-th bit to the MSB position (bit 3)
        // 2. Apply bitwise AND with 8 (binary 1000) to isolate the MSB
        // 3. Shift right by 3 positions to move the isolated bit to the LSB position
        // 4. Cast to char to store the bit value (0 or 1) in dstBits[i]
        bitArray[bitIndex] = (char)((sourceValue << bitIndex & 8) >> 3);
    }
}