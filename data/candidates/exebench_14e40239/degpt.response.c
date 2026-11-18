/**
 * Converts an 8-bit RGB image to a 32-bit RGB image.
 *
 * @param dest_ptr   Pointer to the destination buffer (32-bit RGB).
 * @param dest_width Width of the destination image in pixels.
 * @param dest_height Height of the destination image in pixels.
 * @param dest_pitch Number of bytes per row in the destination buffer.
 * @param dest_x     X-coordinate of the destination rectangle.
 * @param dest_y     Y-coordinate of the destination rectangle.
 * @param dest_dx    Width of the destination rectangle.
 * @param dest_dy    Height of the destination rectangle.
 * @param src_ptr    Pointer to the source buffer (8-bit RGB).
 * @param src_width  Width of the source image in pixels.
 * @param src_height Height of the source image in pixels.
 * @param src_pitch  Number of bytes per row in the source buffer.
 * @param src_x      X-coordinate of the source rectangle.
 * @param src_y      Y-coordinate of the source rectangle.
 * @param src_dx     Width of the source rectangle.
 * @param src_dy     Height of the source rectangle.
 * @return           0 on success, -1 on failure.
 */
int RGB8toRGB32(uchar *dest_buffer, int dest_img_width, int dest_img_height, int dest_row_stride, int dest_rect_x, int dest_rect_y,
                int dest_rect_width, int dest_rect_height, uchar *src_buffer, int src_img_width, int src_img_height, int src_row_stride,
                int src_rect_x, int src_rect_y, int src_rect_width, int src_rect_height)
{
    return -1;
}