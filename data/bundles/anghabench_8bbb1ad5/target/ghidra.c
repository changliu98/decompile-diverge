void RewindBitPosition(size_t new_storage_ix,size_t *storage_ix,uint8_t *storage)

{
  size_t mask;
  size_t bitpos;
  uint8_t *storage_local;
  size_t *storage_ix_local;
  size_t new_storage_ix_local;
  
  storage[new_storage_ix >> 3] =
       storage[new_storage_ix >> 3] & (char)(1 << ((byte)new_storage_ix & 7)) - 1U;
  *storage_ix = new_storage_ix;
  return;
}