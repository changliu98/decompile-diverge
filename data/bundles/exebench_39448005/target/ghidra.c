int FS460_get_available_vga_modes(unsigned_long *p_vga_modes)

{
  unsigned_long *p_vga_modes_local;
  undefined4 local_c;
  
  if (p_vga_modes == (unsigned_long *)0x0) {
    local_c = 0x1000;
  }
  else {
    *p_vga_modes = 0x1f;
    local_c = 0;
  }
  return local_c;
}