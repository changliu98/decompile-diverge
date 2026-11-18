_Bool MACH0_(obj_t *bin,ut32 offset,ut32 size)

{
  _Bool _Var1;
  _Bool r;
  ut32 size_local;
  ut32 offset_local;
  obj_t *bin_local;
  
  _Var1 = parse_chained_fixups(bin,offset,size);
  g_no_tailcall_sink = g_no_tailcall_sink + 1;
  return _Var1;
}