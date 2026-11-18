int __cdecl check_height(avltree *avlt, avlnode *n)
{
  int v3; // [rsp+8h] [rbp-28h]
  int cmp; // [rsp+Ch] [rbp-24h]
  int rh; // [rsp+10h] [rbp-20h]
  int lh; // [rsp+14h] [rbp-1Ch]

  if ( n == &avlt->nil )
    return 0;
  lh = check_height(avlt, n->left);
  if ( lh < 0 )
    return lh;
  rh = check_height(avlt, n->right);
  if ( rh < 0 )
    return rh;
  cmp = rh - lh;
  if ( rh - lh < -1 || cmp > 1 || cmp != n->bf )
    return -1;
  if ( lh <= rh )
    v3 = rh;
  else
    v3 = lh;
  return v3 + 1;
}