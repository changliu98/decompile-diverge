int get_max_vga_mode(unsigned long *p_max_mode)
{
  if (p_max_mode == ((void *)0))
    return (0x1000);
  *p_max_mode = 31;
  return (0);
}