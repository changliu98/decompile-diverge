void remove_node(CC_TreeTable *table,RBNode *z)

{
  RBNode *u;
  int y_color;
  RBNode *y;
  RBNode *x;
  RBNode *z_local;
  CC_TreeTable *table_local;
  
  y_color = (int)z->color;
  if (z->left == table->sentinel) {
    x = z->right;
    transplant(table,z,z->right);
  }
  else if (z->right == table->sentinel) {
    x = z->left;
    transplant(table,z,z->left);
  }
  else {
    u = tree_min(table,z->right);
    y_color = (int)u->color;
    x = u->right;
    if (u->parent == z) {
      x->parent = u;
    }
    else {
      transplant(table,u,u->right);
      u->right = z->right;
      u->right->parent = u;
    }
    transplant(table,z,u);
    u->left = z->left;
    u->left->parent = u;
    u->color = z->color;
  }
  if (y_color == 1) {
    rebalance_after_delete(table,x);
  }
  (*table->mem_free)(z);
  table->size = table->size - 1;
  return;
}