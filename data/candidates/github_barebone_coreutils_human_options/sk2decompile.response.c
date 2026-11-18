static int human_options(const char *opt, unsigned *block, size_t *blocksize) {
  int ret = humblock(opt, blocksize, block);
  if (*blocksize == 0) {
    *blocksize = default_block_size();
    ret = 4;
  }
  return ret;
}