__attribute__((noinline))
void * mrbc_raw_realloc(void *ptr, unsigned int size)
{
  if (ptr != NULL && size == 0) {
    mrbc_raw_free(ptr);
    return NULL;
  }

  MEMORY_POOL *pool = memory_pool;
  volatile USED_BLOCK *target = BLOCK_ADRS(ptr);
  MRBC_ALLOC_MEMSIZE_T alloc_size = size + sizeof(USED_BLOCK);
  FREE_BLOCK *next;

  // align 4 byte
  alloc_size += (-alloc_size & 3);

  // check minimum alloc size.
  if( alloc_size < MRBC_MIN_MEMORY_BLOCK_SIZE ) alloc_size = MRBC_MIN_MEMORY_BLOCK_SIZE;

  // expand? part1.
  // next phys block is free and enough size?
  if( alloc_size > BLOCK_SIZE(target) ) {
    next = PHYS_NEXT(target);
    if( IS_USED_BLOCK(next) ) goto ALLOC_AND_COPY;
    if( (BLOCK_SIZE(target) + BLOCK_SIZE(next)) < alloc_size ) goto ALLOC_AND_COPY;

    remove_free_block( pool, next );
    merge_block((FREE_BLOCK *)target, next);
  }
  next = PHYS_NEXT(target);

  // try shrink.
  FREE_BLOCK *release = split_block((FREE_BLOCK *)target, alloc_size);
  if( release != NULL ) {
    SET_PREV_USED(release);
  } else {
    SET_PREV_USED(next);
    alloc_profile();
    return ptr;
  }

  // check next block, merge?
  if( IS_FREE_BLOCK(next) ) {
    remove_free_block( pool, next );
    merge_block(release, next);
  } else {
    SET_PREV_FREE(next);
  }
  add_free_block( pool, release );
  alloc_profile();
  return ptr;


  // expand part2.
  // new alloc and copy
 ALLOC_AND_COPY: {
    void *new_ptr = mrbc_raw_alloc(size);
    if( new_ptr == NULL ) return NULL;  // ENOMEM

    memcpy(new_ptr, ptr, BLOCK_SIZE(target) - sizeof(USED_BLOCK));
    mrbc_set_vm_id(new_ptr, target->vm_id);

    mrbc_raw_free(ptr);

    return new_ptr;
  }
}