void MotionToFrameCoord(int by,int bx,int my,int mx,int *yP,int *xP)

{
  int *xP_local;
  int *yP_local;
  int mx_local;
  int my_local;
  int bx_local;
  int by_local;
  
  *yP = by * 8 + my;
  *xP = bx * 8 + mx;
  return;
}