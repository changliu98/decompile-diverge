/*
 * Converts a memory handle into a chunk index.
 *
 * This function extracts the relevant bits from the handle by applying
 * a page mask and then shifting the result to obtain the chunk identifier.
 *
 * Parameters:
 *   handle - The memory handle to be converted.
 *
 * Returns:
 *   The chunk index as an unsigned short.
 */
unsigned_short handle_to_chunk_index(unsigned_long memory_handle)
{
    /*
     * Apply PAGE_MASK to isolate the relevant bits of the handle,
     * then right-shift by BUDDY_SHIFT (masked with 0x3f to ensure
     * the shift amount is within valid bounds for the data type).
     */
    return (unsigned_short)((memory_handle & ADDRESS_MASK) >> (CHUNK_SHIFT & 0x3f));
}