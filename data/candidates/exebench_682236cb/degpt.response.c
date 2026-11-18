/**
 * @brief Converts RGB8 pixel data to BGR32 format and copies it to the destination buffer.
 *
 * @param dest_ptr      Pointer to the destination buffer (BGR32 format).
 * @param dest_width    Width of the destination image in pixels.
 * @param dest_height   Height of the destination image in pixels.
 * @param dest_pitch    Pitch (stride) of the destination buffer in bytes.
 * @param dest_x        X coordinate of the top-left corner in the destination buffer.
 * @param dest_y        Y coordinate of the top-left corner in the destination buffer.
 * @param dest_dx       Destination width (region width) to copy.
 * @param dest_dy       Destination height (region height) to copy.
 * @param src_ptr       Pointer to the source buffer (RGB8 format).
 * @param src_width     Width of the source image in pixels.
 * @param src_height    Height of the source image in pixels.
 * @param src_pitch     Pitch (stride) of the source buffer in bytes.
 * @param src_x         X coordinate of the top-left corner in the source buffer.
 * @param src_y         Y coordinate of the top-left corner in the source buffer.
 * @param src_dx        Source width (region width) to read.
 * @param src_dy        Source height (region height) to read.
 * @return              0 on success, -1 on failure.
 */
int RGB8toBGR32(uchar *dest_buffer,int dest_img_width,int dest_img_height,int dest_stride,int dest_rect_x,int dest_rect_y,
               int dest_rect_width,int dest_rect_height,uchar *src_buffer,int src_img_width,int src_img_height,int src_stride,
               int src_rect_x,int src_rect_y,int src_rect_width,int src_rect_height)
{
  return -1;
}