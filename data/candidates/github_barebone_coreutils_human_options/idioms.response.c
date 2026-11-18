static enum strtol_error human_options(char *spec, int *opts, unsigned long *block_size)
{
  enum strtol_error e = humblock(spec, block_size, opts);
  if (*block_size == 0) {
    *block_size = default_block_size();
    return STRTOL_UNRECOGNIZED;
  }
  return e;
}