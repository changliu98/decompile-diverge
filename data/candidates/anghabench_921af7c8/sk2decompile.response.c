static unsigned long handle_to_chunks(unsigned long handle) {
  unsigned long chunks;
  chunks = handle & ~PAGE_MASK;
  chunks >>= PAGE_SHIFT;
  return chunks;
}