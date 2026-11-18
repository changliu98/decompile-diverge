int persistent_cache_read_entry_v3(struct PersistentCache* cache, struct PersistentCacheEntry* entry) {
    struct {
        UINT64 key;
        UINT16 width;
        UINT16 height;
    } header;

    memset(&header, 0, 12);
    
    assert(cache != NULL);
    assert(entry != NULL);

    if (fread(&header, 12, 1, cache->file) != 1) {
        return -1;
    }

    entry->key = header.key;
    entry->width = header.width;
    entry->height = header.height;

    size_t size = (size_t)header.width * header.height * 4;
    if (size > 0xFFFFFFFF) {
        return -1;
    }

    entry->flags = 0;

    if (size > cache->buffer_size) {
        cache->buffer_size = size;
        void* new_buffer = winpr_aligned_recalloc(cache->buffer, cache->buffer_size, 1, 32);
        if (!new_buffer) {
            return -1;
        }
        cache->buffer = new_buffer;
    }

    entry->size = (UINT32)size;
    entry->data = cache->buffer;

    if (fread(entry->data, entry->size, 1, cache->file) != 1) {
        return -1;
    }

    return 1;
}