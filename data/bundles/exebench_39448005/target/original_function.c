int FS460_get_available_vga_modes(unsigned long *p_vga_modes)
{
 if (!p_vga_modes)
  return 0x1000;

 *p_vga_modes =
  0x0001 |
  0x0002 |
  0x0004 |
  0x0008 |
  0x0010;

 return 0;
}