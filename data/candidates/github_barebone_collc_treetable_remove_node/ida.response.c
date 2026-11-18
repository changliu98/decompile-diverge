void __cdecl remove_node(CC_TreeTable *table, RBNode *z)
{
  int y_color; // [rsp+Ch] [rbp-24h]
  RBNode *y; // [rsp+10h] [rbp-20h]
  RBNode *x; // [rsp+18h] [rbp-18h]

  y_color = z->color;
  if ( z->left == table->sentinel )
  {
    x = z->right;
    transplant(table, z, x);
  }
  else if ( z->right == table->sentinel )
  {
    x = z->left;
    transplant(table, z, x);
  }
  else
  {
    y = tree_min(table, z->right);
    y_color = y->color;
    x = y->right;
    if ( y->parent == z )
    {
      x->parent = y;
    }
    else
    {
      transplant(table, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(table, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if ( y_color == 1 )
    rebalance_after_delete(table, x);
  table->mem_free(z);
  --table->size;
}