void *__cdecl mrbc_raw_realloc(void *ptr, unsigned int size)
{
  void *new_ptr;
  FREE_BLOCK *release;
  FREE_BLOCK *next;
  unsigned int alloc_size;
  FREE_BLOCK *target;
  MEMORY_POOL *pool;

  // Handle the standard realloc(ptr, 0) edge case as a free
  if (ptr && !size)
  {
    mrbc_raw_free(ptr);
    return 0LL;
  }

  pool = memory_pool;
  target = (FREE_BLOCK *)((char *)ptr - 4); // Step back to access the block header
  
  // Calculate required allocation size: size + 4-byte header, padded to 4-byte alignment
  alloc_size = (size + 4 + 3) & ~3u;
  if (alloc_size < 32)
    alloc_size = 32;

  // If the current block is already large enough, attempt an in-place split
  if (alloc_size <= GET_BLOCK_SIZE(*(unsigned int *)target))
    goto LABEL_10;

  // Check if the next contiguous block is free and large enough to be merged
  next = (FREE_BLOCK *)((char *)target + GET_BLOCK_SIZE(*(unsigned int *)target));
  if (!IS_BLOCK_ALLOCATED(*(unsigned int *)next) && 
      (GET_BLOCK_SIZE(*(unsigned int *)next) + GET_BLOCK_SIZE(*(unsigned int *)target)) >= alloc_size)
  {
    remove_free_block(pool, next);
    merge_block(target, next);

LABEL_10:
    next = (FREE_BLOCK *)((char *)target + GET_BLOCK_SIZE(*(unsigned int *)target));
    release = split_block(target, alloc_size);
    
    if (release)
    {
      // Mark the newly split rear block as free, and preserve its VM ID
      *(unsigned int *)release = (*(unsigned int *)release & 0xFFFFFD) | 2 | (*(unsigned int *)release & 0xFF000000);
      
      if (IS_BLOCK_ALLOCATED(*(unsigned int *)next))
      {
        // Next block is allocated; just clear its "prev block is allocated" flag
        CLEAR_PREV_ALLOCATED(*(unsigned int *)next);
      }
      else
      {
        // Next block is also free; merge them together
        remove_free_block(pool, next);
        merge_block(release, next);
      }
      add_free_block(pool, release);
      return ptr;
    }
    else
    {
      // Couldn't split (remaining chunk too small); mark next block's "prev allocated" flag
      SET_PREV_ALLOCATED(*(unsigned int *)next);
      return ptr;
    }
  }

  // Fallback: Allocate a new block, copy data, and free the old block
  new_ptr = mrbc_raw_alloc(size);
  if (!new_ptr)
    return 0LL;

  memcpy(new_ptr, ptr, GET_BLOCK_SIZE(*(unsigned int *)target) - 4LL);
  mrbc_set_vm_id(new_ptr, GET_VM_ID(*(unsigned int *)target));
  mrbc_raw_free(ptr);
  
  return new_ptr;
}