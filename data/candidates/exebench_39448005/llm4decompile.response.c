int FS460_get_available_vga_modes(unsigned long *p_vga_modes)
{
 if (!p_vga_modes)
  return 0x1000;

 *p_vga_modes = 0x00000001 |
     0x00000002 |
     0x00000004 |
     0x00000008 |
     0x00000010;

 return 0;
}