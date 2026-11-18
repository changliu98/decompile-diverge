int cal_intervals(int stalls[], int intervals[], int num)
{
 int i = 0;
 int segs = 0;
 int inter = 0;

 while (i < num && stalls[i] == 0)
  i++;

 while (i < num) {
  while (i < num && stalls[i] != 0)
   i++;
  inter = 0;
  while (i < num && stalls[i] == 0) {
   i++;
   inter++;
  }
  if (i < num)
   intervals[segs++] = inter;
 }

 return segs + 1;
}