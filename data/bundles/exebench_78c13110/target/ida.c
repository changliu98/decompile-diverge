void __cdecl MotionToFrameCoord(const int by, const int bx_0, const int my, const int mx, int *const yP, int *const xP)
{
  *yP = my + 8 * by;
  *xP = mx + 8 * bx_0;
}