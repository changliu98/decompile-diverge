int __cdecl check_height(avltree *avlt, avlnode *n)
{
  if (n == &avlt->nil)
    return 0;

  int lh = check_height(avlt, n->left);
  if (lh < 0)
    return lh;

  int rh = check_height(avlt, n->right);
  if (rh < 0)
    return rh;

  int bf = rh - lh;
  
  // Check if the node is unbalanced or if the balance factor is incorrect
  if (bf < -1 || bf > 1 || bf != n->bf)
    return -1;

  return (lh > rh ? lh : rh) + 1;
}