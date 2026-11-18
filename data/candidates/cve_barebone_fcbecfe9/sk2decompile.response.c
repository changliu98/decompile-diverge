void *mrbc_raw_realloc(void *ptr, unsigned int size) {
  if (ptr != NULL && size == 0) {
    mrbc_raw_free(ptr);
    return NULL;
  }
  MEMORY_POOL *pool = mrbc_memory_pool;
  MEMORY_BLOCK *block = (MEMORY_BLOCK *)((char *)ptr - sizeof(MEMORY_BLOCK));
  unsigned int size_with_header = size + sizeof(MEMORY_BLOCK);
  size_with_header += (4 - (size_with_header % 4)) % 4;
  if (size_with_header < sizeof(MEMORY_BLOCK))
    size_with_header = sizeof(MEMORY_BLOCK);
  if (size_with_header > (block->size & 0xFFFFF0C)) {
    MEMORY_BLOCK *next =
        (MEMORY_BLOCK *)((char *)block + (block->size & 0xFFFFF0C));
    if (!(next->size & 0x00000001) &&
        (block->size & 0xFFFFF0C) + (next->size & 0xFFFFF0C) >=
            size_with_header) {
      remove_free_block(pool, next);
      merge_block(block, next);
    } else {
      void *new_block = mrbc_raw_alloc(size);
      if (new_block == NULL) return NULL;
      memcpy(new_block, ptr, (block->size & 0xFFFFF0C) - sizeof(MEMORY_BLOCK));
      mrbc_set_vm_id(new_block, (block->size >> 24) & 0xFF);
      mrbc_raw_free(ptr);
      return new_block;
    }
  }
  MEMORY_BLOCK *next =
      (MEMORY_BLOCK *)((char *)block + (block->size & 0xFFFFF0C));
  MEMORY_BLOCK *new_block = split_block(block, size_with_header);
  if (new_block != NULL) {
    new_block->size = (new_block->size & 0xFFFFF0C) | 0x00000002;
    if (next->size & 0x00000001) {
      next->size &= ~0x00000002;
    } else {
      remove_free_block(pool, next);
      merge_block(new_block, next);
    }
    add_free_block(pool, new_block);
  } else {
    next->size = (next->size & 0xFFFFF0C) | 0x00000002;
  }
  return ptr;
}