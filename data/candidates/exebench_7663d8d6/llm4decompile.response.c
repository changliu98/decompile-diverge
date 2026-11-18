void treemove(struct tree *t, int d, double s)
{
  if (d & 1)
    t->xmin += s;
  else
    t->xmax -= s;
  if (d & 2)
    t->ymin += s;
  else
    t->ymax -= s;
  if (d & 4)
    t->zmin += s;
  else
    t->zmax -= s;
}