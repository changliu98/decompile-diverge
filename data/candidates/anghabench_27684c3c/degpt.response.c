// Resizes the height proportionally based on the change in width.
// Calculates the new height by scaling the old height by the ratio of new_width to old_width.
// Adds a constant offset (DAT_00102008) to the result before casting to an integer.
int resize_height(double initial_width, double target_width, double initial_height)
{
  // Compute scaled height and add offset, then truncate to integer
  return (int)(initial_height * (target_width / initial_width) + height_offset);
}