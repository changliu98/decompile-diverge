xxh_u32 XXH32_finalize(xxh_u32 accumulator, xxh_u8 *data_ptr, size_t remaining_bytes, XXH_alignment alignment)
{
    // Process remaining bytes in 4-byte chunks if possible
    // Mask len to keep only the lower 4 bits (len % 16)
    for (remaining_bytes &= 0xf; 3 < remaining_bytes; remaining_bytes -= 4) {
        // Read 32-bit little-endian value from current pointer with specified alignment
        xxh_u32 chunk_value = XXH_readLE32_align(data_ptr, alignment);
        // Mix the read value into the hash using multiplication and addition
        xxh_u32 mixed_value = chunk_value * -0x3d4d51c3 + accumulator;
        // Advance pointer by 4 bytes
        data_ptr += 4;
        // Finalize the chunk with avalanche-like mixing operations
        accumulator = (mixed_value * 0x20000 | mixed_value >> 0xf) * 0x27d4eb2f;
    }
    // Process remaining bytes one by one (0 to 3 bytes)
    for (; remaining_bytes != 0; remaining_bytes -= 1) {
        // Mix the current byte into the hash
        xxh_u32 mixed_value = (uint)*data_ptr * 0x165667b1 + accumulator;
        // Apply avalanche mixing to the hash
        accumulator = (mixed_value * 0x800 | mixed_value >> 0x15) * -0x61c8864f;
        // Advance pointer by 1 byte
        data_ptr += 1;
    }
    // Apply final avalanche function to ensure good dispersion of bits
    return XXH32_avalanche(accumulator);
}