unsigned __int16 handle_to_chunks(unsigned __int64 handle)
{
  return (handle & ~PAGE_MASK) >> BUDDY_SHIFT;
}