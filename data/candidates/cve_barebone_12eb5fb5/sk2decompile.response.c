static int persistent_cache_read_entry_v3(persistent_cache_t* cache,
                                          persistent_cache_entry_t* entry) {
  persistent_cache_entry_v3_t entry_v3;
  size_t size;
  unsigned char* data;
  memset(&entry_v3, 0, sizeof(entry_v3));
  assert(cache);
  assert(entry);
  if (fread(&entry_v3, sizeof(entry_v3), 1, cache->fp) != 1) {
    return -1;
  }
  entry->type = entry_v3.type;
  entry->width = entry_v3.width;
  entry->height = entry_v3.height;
  size = entry_v3.width * entry_v3.height * 4;
  if (size > 0xffffffff) {
    return -1;
  }
  entry->size = (int)size;
  if (entry->size > cache->max_size) {
    cache->max_size = entry->size;
    data = winpr_aligned_recalloc(cache->data, cache->max_size, 1, 32);
    if (!data) {
      return -1;
    }
    cache->data = data;
  }
  entry->data = cache->data;
  if (fread(entry->data, entry->size, 1, cache->fp) != 1) {
    return -1;
  }
  return 1;
}