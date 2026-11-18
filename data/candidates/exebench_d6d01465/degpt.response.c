/**
 * Converts a 32-bit RGB image to a 24-bit RGB image.
 *
 * @param dest_ptr Pointer to the destination buffer (24-bit RGB).
 * @param dest_width Width of the destination image in pixels.
 * @param dest_height Height of the destination image in pixels.
 * @param dest_pitch Number of bytes per row in the destination buffer.
 * @param dest_x X-coordinate of the destination rectangle origin.
 * @param dest_y Y-coordinate of the destination rectangle origin.
 * @param dest_dx Width of the destination rectangle to write to.
 * @param dest_dy Height of the destination rectangle to write to.
 * @param src_ptr Pointer to the source buffer (32-bit RGB).
 * @param src_width Width of the source image in pixels.
 * @param src_height Height of the source image in pixels.
 * @param src_pitch Number of bytes per row in the source buffer.
 * @param src_x X-coordinate of the source rectangle origin.
 * @param src_y Y-coordinate of the source rectangle origin.
 * @param src_dx Width of the source rectangle to read from.
 * @param src_dy Height of the source rectangle to read from.
 * @return 0 on success, -1 on failure.
 */
int RGB32toRGB24(uchar *dest_ptr,int dest_width,int dest_height,int dest_pitch,int dest_x,int dest_y
                ,int dest_dx,int dest_dy,uchar *src_ptr,int src_width,int src_height,int src_pitch,
                int src_x,int src_y,int src_dx,int src_dy)

{
  return -1;
}