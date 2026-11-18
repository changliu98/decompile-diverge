void add_ang_mom(triangulation *t, vertex *a, vertex *b) {
  t->area += (b->y - a->y) * (b->x2 - a->x2);
  t->area -= (b->y - a->y) * (b->x1 - a->x1);
  t->moment += (b->y - a->y) * (b->x3 - a->x1);
  t->moment -= (b->x - a->x) * (b->x2 - a->x2);
  t->centroid += (b->x - a->x) * (b->x1 - a->x1);
  t->centroid -= (b->y - a->y) * (b->x3 - a->x3);
}