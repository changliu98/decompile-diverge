int check_height(avltree *avlt, avlnode *n)
{
	int lh, rh, cmp;

	if (n == AVL_NIL(avlt))
		return 0;

	lh = check_height(avlt, n->left);
	if (lh < 0)
		return lh;
	
	rh = check_height(avlt, n->right);
	if (rh < 0)
		return rh;
	
	cmp = rh - lh;
	if (cmp < -1 || cmp > 1 || cmp != n->bf) /* check recomputed/cached balance factor */
		return -1;
	
	return 1 + ((lh > rh) ? lh : rh);
}