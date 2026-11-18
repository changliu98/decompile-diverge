int cal_intervals(int *stalls,int *intervals,int num)

{
  bool bVar1;
  int i;
  int inter;
  int segs;
  int num_local;
  int *intervals_local;
  int *stalls_local;
  
  segs = 0;
  i = 0;
  while( true ) {
    bVar1 = false;
    if (i < num) {
      bVar1 = stalls[i] == 0;
    }
    if (!bVar1) break;
    i = i + 1;
  }
  while (i < num) {
    while( true ) {
      bVar1 = false;
      if (i < num) {
        bVar1 = stalls[i] != 0;
      }
      if (!bVar1) break;
      i = i + 1;
    }
    inter = 0;
    while( true ) {
      bVar1 = false;
      if (i < num) {
        bVar1 = stalls[i] == 0;
      }
      if (!bVar1) break;
      i = i + 1;
      inter = inter + 1;
    }
    if (i < num) {
      intervals[segs] = inter;
      segs = segs + 1;
    }
  }
  return segs + 1;
}