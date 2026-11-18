void MotionToFrameCoord(int by, int bx, int my, int mx, int *yP, int *xP)
{
  *yP = my + (by * 8);
  *xP = mx + (bx * 8);
}