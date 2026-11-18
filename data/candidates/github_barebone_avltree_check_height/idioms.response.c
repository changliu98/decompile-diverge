int check_height(struct avltree *avlt, struct avlnode *node)
{
  int lheight; int rheight; int diff; int height;
  if (node == &avlt->nil)
    return 0;
  lheight = check_height(avlt, node->left);
  if (lheight < 0)
    return lheight;
  rheight = check_height(avlt, node->right);
  if (rheight < 0)
    return rheight;
  diff = rheight - lheight;
  if (diff < -1 || diff > 1 || node->bf != diff)
    return -1;
  if (lheight > rheight)
    height = lheight;
  else
    height = rheight;
  return (height + 1);
}