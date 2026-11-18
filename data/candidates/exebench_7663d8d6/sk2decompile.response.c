void treemove(double *box, double d, int dir) {
  if (dir & 1)
    box[0] += d;
  else
    box[3] -= d;
  if (dir & 2)
    box[1] += d;
  else
    box[4] -= d;
  if (dir & 4)
    box[2] += d;
  else
    box[5] -= d;
}