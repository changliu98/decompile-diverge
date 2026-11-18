/*
 * Calculate the MBUS window configuration register offset for a given window index.
 *
 * For windows 0-7, the offset is calculated as (win << 4), which is equivalent to
 * win * 16. This maps to registers at offsets 0x0, 0x10, 0x20, ..., 0x70.
 *
 * For windows 8 and above, the offset is calculated as (win - 8) * 0x10 + 0x900.
 * This maps to registers starting at offset 0x900 for window 8, 0x910 for window 9, etc.
 */
uint mv78xx0_mbus_win_cfg_offset(int window_index)
{
  if (window_index < 8) {
    return window_index << 4;
  }
  return (window_index - 8) * 0x10 + 0x900;
}