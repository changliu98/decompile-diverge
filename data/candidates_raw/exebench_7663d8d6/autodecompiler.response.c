void add_or_subtract_from_node(node *n, double val, int mask) {
  if (mask & 1)
    n->x += val;
  else
    n->x -= val;
  if (mask & 2)
    n->y += val;
  else
    n->y -= val;
  if (mask & 4)
    n->z += val;
  else
    n->z -= val;
}