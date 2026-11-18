int FS460_get_available_vga_modes(unsigned long *p_mode_flags) {
  if (!p_mode_flags) return 0x1000;
  *p_mode_flags = 0x00000001 | 0x00000002 | 0x00000004 | 0x00000008 |
                  0x00000010 | 0x00000020;
  return 0;
}