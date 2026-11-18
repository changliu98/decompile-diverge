void add_to_box(double *box, double delta, int dir)
{
  if (dir & 1)
    box[0] += delta;
  else
    box[3] -= delta;
  if (dir & 2)
    box[1] += delta;
  else
    box[4] -= delta;
  if (dir & 4)
    box[2] += delta;
  else
    box[5] -= delta;
}