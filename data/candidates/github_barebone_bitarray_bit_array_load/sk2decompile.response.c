bool bit_array_load(struct bit_array *ba, FILE *f) {
  unsigned long long size;
  unsigned int nbytes;
  bitmap_word i;
  if (fread(&size, 1, sizeof(size), f) != sizeof(size)) return false;
  size = le64_to_cpu(size);
  bit_array_resize_critical(ba, size);
  nbytes = (ba->word_alloced + 7) >> 3;
  if (fread(ba->word_alloced_ptr, 1, nbytes, f) != nbytes) return false;
  for (i = 0; i < ba->word_max; i++)
    ba->word_alloced_ptr[i] = le64_to_cpu(ba->word_alloced_ptr[i]);
  mask_top_word(ba);
  return true;
}