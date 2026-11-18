int __cdecl plot_digit_wierd(char digit, float row, float col, float hgt, float h, float *vx, float *vy)
{
  int count = 0;
  int i_start, i_end, i;
  float dx, dy;
  float prev_x, prev_y;

  // Check if the character is a digit ('0'-'9')
  if ( digit < 48 || digit > 57 )
    return 0;

  // Determine the start and end indices for the digit's line segments
  i_start = plot_digit_wierd_lt[digit - 47];
  i_end = plot_digit_wierd_lt[digit - 46] - 1;

  for ( i = i_start; i <= i_end; ++i )
  {
    // Extract the 2D coordinates from the packed integer array
    dx = hgt * (float)(plot_digit_wierd_lb[i] / 10);
    dy = h * (float)(plot_digit_wierd_lb[i] % 10);

    // If this is not the first point, form a line segment 
    // from the previous point to the current point
    if ( i != i_start )
    {
      vx[count] = prev_x;
      vy[count] = prev_y;
      vx[count + 1] = row - dx;
      vy[count + 1] = col - dy;
      count += 2;
    }

    // Store the current point to be used as the previous point in the next iteration
    prev_x = row - dx;
    prev_y = col - dy;
  }

  return count;
}