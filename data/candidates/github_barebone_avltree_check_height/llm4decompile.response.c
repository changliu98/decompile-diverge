int check_height(avltree *avlt, avlnode *n)
{
 int lh, rh, bf, height;

 if (n == &avlt->nil)
  return 0;

 lh = check_height(avlt, n->left);
 if (lh < 0)
  return -1;

 rh = check_height(avlt, n->right);
 if (rh < 0)
  return -1;

 bf = rh - lh;
 if (bf < -1 || bf > 1 || bf != n->bf)
  return -1;

 height = lh > rh ? lh : rh;
 return height + 1;
}