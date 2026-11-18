size_t spc_used(size_t head, size_t tail, size_t size)
{
 int diff = head - tail;

 if (diff < 0)
  return size + diff;
 else
  return diff;
}