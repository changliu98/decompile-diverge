static inline int rbtree_rightmost(int x, int n)
{
  return (x + 1) & (n - 1);
}