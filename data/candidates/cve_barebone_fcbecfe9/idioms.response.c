void *mrbc_raw_realloc(void *ptr, unsigned int size)
{
  if (ptr != ((void *)0) && size == 0)
  {
    __myfree(ptr);
    return ((void *)0);
  }
  struct MEMORY_POOL *pool = ((void *)0);
  struct FREE_BLOCK *block = ((void *)0);
  struct FREE_BLOCK *next = ((void *)0);
  struct FREE_BLOCK *new_block = ((void *)0);
  unsigned int alloc_size = size + sizeof(size_t);
  alloc_size += (-(alloc_size) & 3);
  if (alloc_size < 32)
    alloc_size = 32;
  pool = &memory_pool;
  block = (struct FREE_BLOCK *)((void *)((char *)ptr - sizeof(size_t)));
  if (block->size & 1)
  {
    next = (struct FREE_BLOCK *)((void *)((char *)block + block->size));
    if (next->size & 1 ||
        block->size + next->size < alloc_size)
    {
      new_block = __myalloc(size);
      if (new_block == ((void *)0))
        return ((void *)0);
      __mycopy(new_block, ptr, (block->size - sizeof(size_t)));
      __mycopy(new_block + (block->size - sizeof(size_t)),
               (void *)((char *)block + sizeof(size_t)),
               sizeof(size_t));
      __myfree(ptr);
      return new_block;
    }
    else
    {
      __myfree(pool, next);
      __mymerge(block, next);
    }
  }
  else
  {
    next = (struct FREE_BLOCK *)((void *)((char *)block + block->size));
    if (next->size & 1 ||
        block->size + next->size < alloc_size)
    {
      new_block = __myalloc(size);
      if (new_block == ((void *)0))
        return ((void *)0);
      __mycopy(new_block, ptr, (block->size - sizeof(size_t)));
      __mycopy(new_block + (block->size - sizeof(size_t)),
               (void *)((char *)block + sizeof(size_t)),
               sizeof(size_t));
      __myfree(ptr);
      return new_block;
    }
    else
    {
      __myfree(pool, next);
      __mymerge(block, next);
    }
  }
  new_block = __mysplit(block, alloc_size);
  if (new_block == ((void *)0))
  {
    next->size = (next->size & ~1) | 2 | (next->size & 0xff000000);
    return ptr;
  }
  new_block->size = (new_block->size & ~1) | 2 | (new_block->size & 0xff000000);
  if (next->size & 1)
    next->size = (next->size & ~1);
  else
  {
    __myfree(pool, next);
    __mymerge(new_block, next);
  }
  __myadd(pool, new_block);
  return ptr;
}