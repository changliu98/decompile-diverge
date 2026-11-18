int FS460_get_available_vga_modes(unsigned long *p_max_mode)
{
  if (p_max_mode == ((void *)0))
    return (0x1000);
  *p_max_mode = 31;
  return (0);
}