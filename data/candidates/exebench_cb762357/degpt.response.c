void scale_mat(int *matrix,int scale_x,int scale_y)
{
  // Scale the horizontal components (x-axis) if the scale factor is not identity (0x400)
  if (scale_x != 0x400) {
    // Apply horizontal scaling to the first column elements
    *matrix = (*matrix * scale_x) / 0x400;
    matrix[2] = (matrix[2] * scale_x) / 0x400;
    matrix[4] = (matrix[4] * scale_x) / 0x400;
  }
  // Scale the vertical components (y-axis) if the scale factor is not identity (0x400)
  if (scale_y != 0x400) {
    // Apply vertical scaling to the second column elements
    matrix[1] = (matrix[1] * scale_y) / 0x400;
    matrix[3] = (matrix[3] * scale_y) / 0x400;
    matrix[5] = (matrix[5] * scale_y) / 0x400;
  }
}