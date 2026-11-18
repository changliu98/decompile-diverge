// Unpacks an immediate value into a byte and a shift amount.
// Returns 1 if successful, 0 otherwise.
int UnpackImmediate(uint immediateValue, int *decodedByte, int *decodedShift)
{
    // Handle the special case where the value is zero
    if (immediateValue == 0) {
        *decodedByte = 0;
        *decodedShift = 0;
        return 1;
    }

    // Iterate up to 15 times to check for valid immediate encoding
    for (int shiftCount = 0; shiftCount < 0xf; shiftCount++) {
        // Check if the two least significant bits are non-zero
        if ((immediateValue & 3) != 0) {
            // If the remaining value fits in 8 bits, it's a valid immediate
            if (immediateValue < 0x100) {
                *decodedByte = immediateValue;
                *decodedShift = shiftCount;
                return 1;
            }
            // Otherwise, the immediate is invalid
            return 0;
        }
        // Shift right by 2 bits to check the next pair of bits
        immediateValue >>= 2;
    }
    // If no valid immediate is found after all iterations
    return 0;
}