unsigned __int16 __cdecl handle_to_chunks(unsigned __int64 handle)
{
  return (~PAGE_MASK & handle) >> BUDDY_SHIFT;
}