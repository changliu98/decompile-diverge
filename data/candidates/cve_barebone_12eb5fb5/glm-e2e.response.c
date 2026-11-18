int persistent_cache_read_entry_v3(PersistentCache *cache, CacheEntry *entry) {
    uint8_t header[12];
    size_t total_size;

    memset(header, 0, sizeof(header));

    assert(cache != NULL);
    assert(entry != NULL);

    if (fread(header, 1, 12, cache->file) != 1) {
        return -1;
    }

    // Unpack header (assuming little-endian)
    entry->field_0x00 = *(uint64_t *)&header[0];
    entry->field_0x08 = *(uint16_t *)&header[8];
    entry->field_0x0a = *(uint16_t *)&header[10];

    total_size = (size_t)entry->field_0x08 * 4 * entry->field_0x0a;

    if (total_size > 0xFFFFFFFF) {
        return -1;
    }

    entry->size = (uint32_t)total_size;
    entry->field_0x10 = 0;

    if (entry->size > cache->buffer_size) {
        cache->buffer_size = entry->size;
        void *new_buffer = winpr_aligned_recalloc(cache->buffer, cache->buffer_size, 1, 32);
        if (!new_buffer) {
            return -1;
        }
        cache->buffer = new_buffer;
    }

    entry->data = cache->buffer;

    if (fread(entry->data, 1, entry->size, cache->file) != 1) {
        return -1;
    }

    return 1;
}