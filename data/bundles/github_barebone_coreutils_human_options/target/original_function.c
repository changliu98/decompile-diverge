enum strtol_error
human_options (char const *spec, int *opts, uintmax_t *block_size)
{
  strtol_error e = humblock (spec, block_size, opts);
  if (*block_size == 0)
    {
      *block_size = default_block_size ();
      e = LONGINT_INVALID;
    }
  return e;
}