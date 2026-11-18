void MotionToFrameCoord(int x, int y, int x_offset, int y_offset, int *x_frame,
                        int *y_frame) {
  *x_frame = x_offset + (x << 3);
  *y_frame = y_offset + (y << 3);
  return;
}