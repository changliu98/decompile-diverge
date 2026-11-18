void *mrbc_raw_realloc(void *ptr, unsigned int size)
{
  MEMORY_POOL *pool = memory_pool;
  FREE_BLOCK *release;
  FREE_BLOCK *next;
  FREE_BLOCK *prev;
  USED_BLOCK *target;
  void *new_ptr;
  unsigned int alloc_size;


  if( ptr == NULL ) {
    return mrbc_raw_alloc(size);
  }


  if( size == 0 ) {
    mrbc_raw_free(ptr);
    return NULL;
  }


  target = (USED_BLOCK*)((uint8_t*)ptr - sizeof(USED_BLOCK));
  alloc_size = sizeof(USED_BLOCK) + size;
  alloc_size += (4 - (alloc_size % 4)) % 4;
  if( alloc_size < sizeof(FREE_BLOCK) ) {
    alloc_size = sizeof(FREE_BLOCK);
  }


  if( alloc_size > (target->size & 0xFFFFFFFCU) ) {

    next = (FREE_BLOCK*)((uint8_t*)target + (target->size & 0xFFFFFFFCU));
    if( ((next->size & 0x01) == 0) &&
        ((target->size & 0xFFFFFFFCU) + (next->size & 0xFFFFFFFCU)) >= alloc_size ) {

      remove_free_block(pool, next);
      merge_block(target, next);
    } else {

      new_ptr = mrbc_raw_alloc(size);
      if( new_ptr == NULL ) {
        return NULL;
      }


      memcpy(new_ptr, ptr, (target->size & 0xFFFFFFFCU) - sizeof(USED_BLOCK));


      mrbc_set_vm_id(new_ptr, (target->size >> 24));


      mrbc_raw_free(ptr);

      return new_ptr;
    }
  }


  next = (FREE_BLOCK*)((uint8_t*)target + (target->size & 0xFFFFFFFCU));
  release = split_block(target, alloc_size);
  if( release != NULL ) {

    ((release)->size = ((release)->size & 0xFF000000U) | ((target->size & 0xFFFFFFFCU) - sizeof(USED_BLOCK)) | 0x02);
    if( ((next->size & 0x01) == 0) ) {

      remove_free_block(pool, next);
      merge_block(release, next);
    } else {

      ((next)->size = ((next)->size & 0xFF000000U) | ((next->size & 0xFFFFFFFCU) - sizeof(USED_BLOCK)) | 0x00);
    }
    add_free_block(pool, release);
  } else {

    ((next)->size = ((next)->size & 0xFF000000U) | ((next->size & 0xFFFFFFFCU) - sizeof(USED_BLOCK)) | 0x02);
  }

  return ptr;
}