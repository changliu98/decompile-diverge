void InitTwoInts(int x, int y, struct TwoInts *Q, struct TwoInts *R, int *P)
{
   Q->first = Q->second = x;
   *P = y;
   R->first = x;
   R->second = y;
}