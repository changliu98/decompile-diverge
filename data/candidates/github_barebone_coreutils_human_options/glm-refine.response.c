strtol_error __cdecl human_options(const char *spec, int *opts, uintmax_t *block_size)
{
  strtol_error error = humblock(spec, block_size, opts);
  
  if (*block_size == 0)
  {
    *block_size = default_block_size();
    return 4; // 4 typically corresponds to strtol_error's "invalid suffix" or similar error code
  }
  
  return error;
}