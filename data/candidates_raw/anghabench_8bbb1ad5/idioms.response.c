void set_bit(unsigned long new_storage_ix, unsigned long *storage_ix, unsigned char *storage)
{
  unsigned long storage_ix_bit = *storage_ix;
  unsigned long storage_ix_byte = *storage_ix / 8;
  unsigned long storage_ix_bit_mask = 1 << (*storage_ix % 8);
  storage[storage_ix_byte] = storage[storage_ix_byte] & ~(storage_ix_bit_mask);
  *storage_ix = new_storage_ix;
  return;
}