int persistent_cache_read_entry_v3(rdpPersistentCache *persistent, PERSISTENT_CACHE_ENTRY *entry)
{
    PERSISTENT_CACHE_ENTRY_V3 raw_entry_data; // Temporary structure to hold raw V3 entry data from file
    UINT64 bitmap_data_size; // Calculated size of the bitmap data
    BYTE *reallocated_buffer; // Temporary pointer for reallocation

    // Initialize the temporary entry structure to zero
    memset(&raw_entry_data, 0, sizeof(raw_entry_data));
    
    // Validate that the persistent cache pointer is not NULL
    if (persistent == NULL) {
        __assert_fail("persistent", "/work/harness.c", 0x117,
                      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
    }
    
    // Validate that the output entry pointer is not NULL
    if (entry == NULL) {
        __assert_fail("entry", "/work/harness.c", 0x118,
                      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
    }

    // Read the V3 entry header from the file
    if (fread(&raw_entry_data, sizeof(raw_entry_data), 1, persistent->fp) != 1) {
        return -1;
    }

    // Copy key and dimensions from the raw entry to the output entry structure
    entry->key64 = raw_entry_data.key64;
    entry->width = raw_entry_data.width;
    entry->height = raw_entry_data.height;

    // Calculate the total size of the bitmap data (width * height * 4 bytes per pixel)
    bitmap_data_size = (UINT64)raw_entry_data.width * 4 * (UINT64)raw_entry_data.height;

    // Check for integer overflow or excessively large size (greater than 4GB)
    if (bitmap_data_size >= 0x100000000ULL) {
        return -1;
    }

    // Initialize flags and store the calculated size in the entry
    entry->flags = 0;
    entry->size = (UINT32)bitmap_data_size;

    // Ensure the persistent cache has enough allocated memory for the bitmap data
    if (persistent->bmpSize < bitmap_data_size) {
        // Attempt to reallocate memory, increasing capacity to at least 32 bytes more than needed
        reallocated_buffer = winpr_aligned_recalloc(persistent->bmpData, persistent->bmpSize, 1, 0x20);
        if (reallocated_buffer == NULL) {
            return -1;
        }
        // Update the persistent cache's data pointer and size
        persistent->bmpData = reallocated_buffer;
        persistent->bmpSize = bitmap_data_size;
    }

    // Point the entry's data buffer to the persistent cache's allocated memory
    entry->data = persistent->bmpData;

    // Read the bitmap data into the allocated buffer
    if (fread(entry->data, bitmap_data_size, 1, persistent->fp) != 1) {
        return -1;
    }

    // Return success
    return 1;
}