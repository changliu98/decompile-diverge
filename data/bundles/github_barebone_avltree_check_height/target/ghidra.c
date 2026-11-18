int check_height(avltree *avlt,avlnode *n)

{
  int iVar1;
  int iVar2;
  int local_30;
  int cmp;
  int rh;
  int lh;
  avlnode *n_local;
  avltree *avlt_local;
  int local_c;
  
  if (n == &avlt->nil) {
    local_c = 0;
  }
  else {
    iVar1 = check_height(avlt,n->left);
    local_c = iVar1;
    if ((-1 < iVar1) && (local_30 = check_height(avlt,n->right), local_c = local_30, -1 < local_30))
    {
      iVar2 = local_30 - iVar1;
      if ((iVar2 < -1) || ((1 < iVar2 || (iVar2 != n->bf)))) {
        local_c = -1;
      }
      else {
        if (local_30 < iVar1) {
          local_30 = iVar1;
        }
        local_c = local_30 + 1;
      }
    }
  }
  return local_c;
}