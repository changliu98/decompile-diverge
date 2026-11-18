// Replicates boundary pixels for image processing
// img: pointer to the image data array
// w: width of the image
// h: height of the image
// x: x-coordinate of the pixel to retrieve
// y: y-coordinate of the pixel to retrieve
// bnd_const: boundary constant (unused in this implementation)
// Returns the pixel value at (x, y), clamping coordinates to image boundaries
float KBND_REPLICATE(float *image_data, int width, int height, int col, int row, float boundary_constant)
{
  // Clamp x coordinate to [0, w-1]
  if (col < 0) col = 0;
  if (col >= width) col = width - 1;
  // Clamp y coordinate to [0, h-1]
  if (row < 0) row = 0;
  if (row >= height) row = height - 1;
  // Return the pixel value at the clamped coordinates
  return image_data[row * width + col];
}