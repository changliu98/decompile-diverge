bool __cdecl strip_trailing_slashes(char *file)
{
  bool had_slash; // [rsp+17h] [rbp-19h]
  char *base_lim; // [rsp+18h] [rbp-18h]
  char *base; // [rsp+20h] [rbp-10h]

  base = last_component(file);
  if ( !*base )
    base = file;
  base_lim = &base[base_len(base)];
  had_slash = *base_lim != 0;
  *base_lim = 0;
  return had_slash;
}