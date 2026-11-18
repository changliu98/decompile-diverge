unsigned_short handle_to_chunks(unsigned_long handle)

{
  unsigned_long handle_local;
  
  return (unsigned_short)((handle & (PAGE_MASK ^ 0xffffffffffffffff)) >> ((byte)BUDDY_SHIFT & 0x3f))
  ;
}