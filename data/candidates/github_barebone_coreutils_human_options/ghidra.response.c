strtol_error human_options(char *spec,int *opts,uintmax_t *block_size)

{
  uintmax_t uVar1;
  strtol_error e;
  uintmax_t *block_size_local;
  int *opts_local;
  char *spec_local;
  
  e = humblock(spec,block_size,opts);
  if (*block_size == 0) {
    uVar1 = default_block_size();
    *block_size = uVar1;
    e = LONGINT_INVALID;
  }
  return e;
}