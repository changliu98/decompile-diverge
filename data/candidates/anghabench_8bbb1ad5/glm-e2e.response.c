void RewindBitPosition(uint64_t bit_pos, uint64_t *current_pos, uint8_t *buffer) {
    // Calculate the bit offset within the current byte (bit_pos % 8)
    uint64_t bit_offset = bit_pos & 0x7;
    
    // Create a bitmask to clear the remaining bits in the byte
    // e.g., if bit_offset is 3, mask becomes (1 << 3) - 1 = 0b00000111
    uint8_t mask = (uint8_t)((1ULL << bit_offset) - 1);
    
    // Calculate the byte index in the buffer (bit_pos / 8)
    uint64_t byte_index = bit_pos >> 3;
    
    // Clear the bits after the rewind position to avoid leftover data
    buffer[byte_index] &= mask;
    
    // Update the current bit position
    *current_pos = bit_pos;
}