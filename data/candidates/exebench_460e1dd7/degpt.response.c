void BinaryFiles__swap_bytes32(uint *data)
{
    // Swap the byte order of a 32-bit unsigned integer (endianness conversion)
    *data = (*data & 0xff000000) >> 24 |  // Move most significant byte to least significant position
             (*data & 0x00ff0000) >> 8  |  // Move second byte to third position
             (*data & 0x0000ff00) << 8  |  // Move third byte to second position
             (*data & 0x000000ff) << 24;   // Move least significant byte to most significant position
}