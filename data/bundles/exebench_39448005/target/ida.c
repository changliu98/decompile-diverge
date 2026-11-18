int __cdecl FS460_get_available_vga_modes(unsigned __int64 *p_vga_modes)
{
  if ( !p_vga_modes )
    return 4096;
  *p_vga_modes = 31LL;
  return 0;
}