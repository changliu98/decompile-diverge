static inline int bnode_link_set_leaf(void *lock)
{
  return ((int)(*((unsigned long *)lock)) & 1);
}