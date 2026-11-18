int enddata(char *buffer, int current_position)
{
    // Calculate the number of padding bytes needed to align p to a 64-byte boundary
    // uVar1 = p % 64
    int padding_bytes_needed = current_position & 0x3f;
    
    // If padding is needed (uVar1 != 0), write the padding count into the buffer
    // The padding byte is stored at position (p - uVar1 + 1) and contains the value (uVar1 - 1)
    if (padding_bytes_needed != 0) {
        buffer[current_position - padding_bytes_needed + 1] = (char)(padding_bytes_needed - 1);
    }
    
    // If no padding was needed (uVar1 == 0), return 0
    // Otherwise, return the new position after adding 64 bytes of padding
    return (padding_bytes_needed == 0) ? 0 : (current_position - padding_bytes_needed + 0x40);
}