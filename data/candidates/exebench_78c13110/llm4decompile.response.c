void MotionToFrameCoord(int by, int bx, int my, int mx, int *yP, int *xP)
{
  *yP = 8*by + my;
  *xP = 8*bx + mx;
}