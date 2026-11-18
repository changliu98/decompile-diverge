static int check_height(AVLTree *tree, AVLTreeNode *node) {
  int lh, rh, bf;
  if (node == &tree->nil) return 0;
  lh = check_height(tree, node->left);
  if (lh < 0) return lh;
  rh = check_height(tree, node->right);
  if (rh < 0) return rh;
  bf = rh - lh;
  if (bf < -1 || bf > 1 || bf != node->balance_factor) return -1;
  return (lh > rh ? lh : rh) + 1;
}