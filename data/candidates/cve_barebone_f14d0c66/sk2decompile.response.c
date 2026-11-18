int persistent_cache_read_entry_v3(persistent_cache_t* cache,
                                   persistent_cache_entry_t* entry) {
  persistent_cache_entry_v3_t entry_v3;
  uint32 size;
  void* p;
  memset(&entry_v3, 0, sizeof(entry_v3));
  assert(cache);
  assert(entry);
  if (fread(&entry_v3, sizeof(entry_v3), 1, cache->file) != 1) {
    return -1;
  }
  entry->key = entry_v3.key;
  entry->width = entry_v3.width;
  entry->height = entry_v3.height;
  size = entry_v3.width * entry_v3.height * 4;
  if (size > 0xffffffff) {
    return -1;
  }
  entry->flags = 0;
  if (size > cache->buffer_size) {
    cache->buffer_size = size;
    p = realloc(cache->buffer, cache->buffer_size);
    if (!p) {
      return -1;
    }
    cache->buffer = p;
  }
  entry->size = size;
  entry->data = cache->buffer;
  if (fread(entry->data, entry->size, 1, cache->file) != 1) {
    return -1;
  }
  return 1;
}