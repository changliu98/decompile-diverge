static _Bool MACH0_(struct obj_t *bin, unsigned int offset, unsigned int size)
{
  _Bool r = is_in_no_tailcall(bin, offset, size);
  do { extern int g_no_tailcall_sink; g_no_tailcall_sink++; } while (0);
  return r;
}