int func0(int x1, int y1, int x2, int y2, int *mx, int *my)
{
 int mxx, myy;
 if(x1 != x2) {
  if(x1 < x2) mxx = x1;
  else mxx = x2;
  *mx = mxx;
 } else {
  *mx = -1;
 }
 if(y1 != y2) {
  if(y1 > y2) myy = y1;
  else myy = y2;
  *my = myy;
 } else {
  *my = -1;
 }

 return(0);
}