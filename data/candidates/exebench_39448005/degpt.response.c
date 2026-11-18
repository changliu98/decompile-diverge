// Function to retrieve available VGA modes
// Parameters:
//   p_vga_modes: Pointer to store the available VGA modes bitmask
// Returns:
//   0 on success, 0x1000 if p_vga_modes is NULL
int FS460_get_available_vga_modes(unsigned_long *vga_modes_mask)
{
  // Check if the input pointer is NULL
  if (vga_modes_mask == (unsigned_long *)0x0) {
    // Return error code if pointer is invalid
    return 0x1000;
  }
  // Set the available VGA modes bitmask to 0x1f
  *vga_modes_mask = 0x1f;
  // Return success
  return 0;
}