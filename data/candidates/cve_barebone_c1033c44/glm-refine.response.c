define GC_OUT_OF_MEMORY_FLAG 0x10

void *__cdecl mrb_realloc(mrb_state *mrb, void *p, size_t len)
{
  void *p2;

  p2 = mrb_realloc_simple(mrb, p, len);
  
  // If the requested length is 0, return immediately regardless of success/failure.
  // This mimics standard `realloc(p, 0)` behavior which may free the pointer and return NULL.
  if ( !len )
    return p2;

  if ( p2 )
  {
    // Allocation successful: clear the out-of-memory flag
    *((_BYTE *)&mrb->gc + 96) &= ~GC_OUT_OF_MEMORY_FLAG;
  }
  else
  {
    // Allocation failed: 
    // 1. Free the original pointer to prevent memory leaks
    mrb_free(mrb, p);
    
    // 2. Set the out-of-memory flag (0x10) while preserving other flags (using bitwise OR with 0xEF)
    *((_BYTE *)&mrb->gc + 96) = (*((_BYTE *)&mrb->gc + 96) & 0xEF) | GC_OUT_OF_MEMORY_FLAG;
    
    // 3. Raise the out-of-memory exception
    mrb_raise_nomemory(mrb);
  }
  
  return p2;
}