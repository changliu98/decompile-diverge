void RewindBitPosition(size_t new_storage_ix, size_t *storage_ix,
                       uint8_t *storage) {
  storage[new_storage_ix >> 3] &= (1 << (new_storage_ix & 7)) - 1;
  *storage_ix = new_storage_ix;
}