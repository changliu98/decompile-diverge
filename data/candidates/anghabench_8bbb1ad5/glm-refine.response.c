void __cdecl RewindBitPosition(const size_t new_storage_ix, size_t *storage_ix, uint8_t *storage)
{
    // Create a bitmask that keeps only the bits below the new bit position.
    // For example, if new_storage_ix is 5, the mask becomes (1 << 5) - 1 = 31 (0b00011111).
    uint8_t bitmask = (1 << (new_storage_ix & 7)) - 1;
    
    // Clear the bits in the target byte from the new position upwards
    storage[new_storage_ix >> 3] &= bitmask;
    
    // Update the bit index pointer to the new position
    *storage_ix = new_storage_ix;
}