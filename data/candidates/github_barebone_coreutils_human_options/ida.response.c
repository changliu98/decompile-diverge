strtol_error __cdecl human_options(const char *spec, int *opts, uintmax_t *block_size)
{
  strtol_error e; // [rsp+4h] [rbp-1Ch]

  e = humblock(spec, block_size, opts);
  if ( !*block_size )
  {
    *block_size = default_block_size();
    return 4;
  }
  return e;
}