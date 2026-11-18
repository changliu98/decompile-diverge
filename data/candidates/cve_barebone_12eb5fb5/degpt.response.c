int read_v3_cache_entry(rdpPersistentCache *cache_handle, PERSISTENT_CACHE_ENTRY *output_entry)
{
    PERSISTENT_CACHE_ENTRY_V3 v3_entry_data; // Temporary structure to read the V3 format entry from disk
    UINT64 image_data_size;                      // Calculated size of the image data

    memset(&v3_entry_data, 0, sizeof(v3_entry_data)); // Initialize temporary entry structure to zero

    if (cache_handle == NULL) {
        __assert_fail("persistent", "/work/harness.c", 0x71,
                      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
    }
    if (output_entry == NULL) {
        __assert_fail("entry", "/work/harness.c", 0x72,
                      "int persistent_cache_read_entry_v3(rdpPersistentCache *, PERSISTENT_CACHE_ENTRY *)");
    }

    // Read the V3 header entry from the persistent cache file
    if (fread(&v3_entry_data, sizeof(v3_entry_data), 1, cache_handle->fp) != 1) {
        return -1;
    }

    // Copy basic metadata from the V3 entry to the output entry structure
    output_entry->key64 = v3_entry_data.key64;
    output_entry->width = v3_entry_data.width;
    output_entry->height = v3_entry_data.height;

    // Calculate the total size of the bitmap data (width * height * 4 bytes per pixel)
    image_data_size = (UINT64)v3_entry_data.width * 4 * (UINT64)v3_entry_data.height;

    // Check for integer overflow or excessively large size (max 1GB)
    if (image_data_size >= 0x100000000) {
        return -1;
    }

    output_entry->size = (UINT32)image_data_size;
    output_entry->flags = 0;

    // Ensure the allocated buffer is large enough to hold the image data
    if (cache_handle->bmpSize < output_entry->size) {
        BYTE *reallocated_buffer = winpr_aligned_recalloc(cache_handle->bmpData, (size_t)cache_handle->bmpSize, 1, 0x20);
        if (reallocated_buffer == NULL) {
            return -1;
        }
        cache_handle->bmpSize = output_entry->size;
        cache_handle->bmpData = reallocated_buffer;
    }

    // Point the entry's data field to the allocated buffer
    output_entry->data = cache_handle->bmpData;

    // Read the actual image data into the allocated buffer
    if (fread(output_entry->data, output_entry->size, 1, cache_handle->fp) != 1) {
        return -1;
    }

    return 1;
}