void *mrbc_raw_realloc( void *ptr, int size )
{
  struct HEAP_HEADER *head, *prev, *next, *split;
  struct MEMORY_POOL *pool = memory_pool;
  unsigned char *new_ptr;
  int alloc_size;


  if( ptr == NULL && size == 0 ) {
    mrbc_raw_free(ptr);
    return NULL;
  }


  head = (struct HEAP_HEADER *)((char *)ptr + sizeof(struct HEAP_HEADER) - sizeof(char));
  alloc_size = size + sizeof(struct HEAP_HEADER);

  alloc_size += (4 - (alloc_size % 4)) % 4;

  if( alloc_size < 32 ) alloc_size = 32;

  if( ((head->size & 0x00ffffff) & ~0x3) < alloc_size ) {

    next = (struct HEAP_HEADER *)((char *)head + ((head->size & 0x00ffffff) & ~0x3));

    if( ((next->size & 0x00ffffff) & 1) != 0 || alloc_size > (((head->size & 0x00ffffff) & ~0x3) + ((next->size & 0x00ffffff) & ~0x3)) ) {


      goto ALLOC_AND_COPY;
    }


    remove_free_block(pool, next);


    merge_block(head, next);


  }

  next = (struct HEAP_HEADER *)((char *)head + ((head->size & 0x00ffffff) & ~0x3));


  split = split_block(head, alloc_size);
  if( split != NULL ) {

    split->size = ((split->size & 0xff000000) | ((split->size & 0x00ffffff) & ~0x3) | 0x2);


  } else {




    next->size = ((next->size & 0xff000000) | ((next->size & 0x00ffffff) & ~0x3) | 0x2);
    new_ptr = ptr;
    return new_ptr;
  }


  if( ((next->size & 0x00ffffff) & 1) == 0 ) {

    remove_free_block(pool, next);


    merge_block(split, next);
  } else {

    next->size = ((next->size & 0xff000000) | ((next->size & 0x00ffffff) & ~0x3) | 0x0);
  }


  add_free_block(pool, split);


  new_ptr = ptr;
  return new_ptr;

ALLOC_AND_COPY:
  new_ptr = mrbc_raw_alloc(size);
  if( new_ptr == NULL ) return NULL;

  memcpy(new_ptr, ptr, ((head->size & 0x00ffffff) & ~0x3) - sizeof(struct HEAP_HEADER));
  mrbc_set_vm_id(new_ptr, ((head->size >> 24) & 0xff));
  mrbc_raw_free(ptr);
  return new_ptr;
}