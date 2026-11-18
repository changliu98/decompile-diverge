void *__cdecl mrbc_raw_realloc(void *ptr, unsigned int size)
{
  void *new_ptr; // [rsp+8h] [rbp-48h]
  FREE_BLOCK *release; // [rsp+10h] [rbp-40h]
  FREE_BLOCK *next; // [rsp+18h] [rbp-38h]
  FREE_BLOCK *nexta; // [rsp+18h] [rbp-38h]
  unsigned int alloc_size; // [rsp+24h] [rbp-2Ch]
  FREE_BLOCK *target; // [rsp+28h] [rbp-28h]
  MEMORY_POOL *pool; // [rsp+30h] [rbp-20h]

  if ( ptr && !size )
  {
    mrbc_raw_free(ptr);
    return 0LL;
  }
  pool = memory_pool;
  target = (FREE_BLOCK *)((char *)ptr - 4);
  alloc_size = size + 4 + (-(char)(size + 4) & 3);
  if ( alloc_size < 0x20uLL )
    alloc_size = 32;
  if ( alloc_size <= (*(_DWORD *)target & 0xFFFFFCu) )
    goto LABEL_10;
  next = (FREE_BLOCK *)((char *)target + (*(_DWORD *)target & 0xFFFFFC));
  if ( (*(_DWORD *)next & 1) == 0 && (*(_DWORD *)next & 0xFFFFFC) + (*(_DWORD *)target & 0xFFFFFCu) >= alloc_size )
  {
    remove_free_block(memory_pool, next);
    merge_block(target, next);
LABEL_10:
    nexta = (FREE_BLOCK *)((char *)target + (*(_DWORD *)target & 0xFFFFFC));
    release = split_block(target, alloc_size);
    if ( release )
    {
      *(_DWORD *)release = *(_DWORD *)release & 0xFFFFFD | 2 | *(_DWORD *)release & 0xFF000000;
      if ( (*(_DWORD *)nexta & 1) != 0 )
      {
        *(_DWORD *)nexta &= ~2u;
      }
      else
      {
        remove_free_block(pool, nexta);
        merge_block(release, nexta);
      }
      add_free_block(pool, release);
      return ptr;
    }
    else
    {
      *(_DWORD *)nexta = *(_DWORD *)nexta & 0xFFFFFD | 2 | *(_DWORD *)nexta & 0xFF000000;
      return ptr;
    }
  }
  new_ptr = mrbc_raw_alloc(size);
  if ( !new_ptr )
    return 0LL;
  memcpy(new_ptr, ptr, (*(_DWORD *)target & 0xFFFFFC) - 4LL);
  mrbc_set_vm_id(new_ptr, HIBYTE(*(_DWORD *)target));
  mrbc_raw_free(ptr);
  return new_ptr;
}