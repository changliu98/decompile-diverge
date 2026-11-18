// Writes a 16-bit integer (w) into a character buffer (p) in little-endian byte order.
// Only the lower 16 bits of w are written; the upper bits are ignored.
// Returns the original value of w.
int putdword(char *buffer, int value)
{
    // Store the least significant byte of w at the first position
    *buffer = (char)value;
    // Store the next byte of w at the second position
    buffer[1] = (char)((uint)value >> 8);
    // Return the original integer value
    return value;
}