void rebalance_after_delete(CC_TreeTable *table,RBNode *x)

{
  bool bVar1;
  RBNode *w;
  RBNode *x_local;
  CC_TreeTable *table_local;
  
  x_local = x;
  while( true ) {
    bVar1 = false;
    if (x_local != table->root) {
      bVar1 = x_local->color == '\x01';
    }
    if (!bVar1) break;
    if (x_local == x_local->parent->left) {
      w = x_local->parent->right;
      if (w->color == '\0') {
        w->color = '\x01';
        x_local->parent->color = '\0';
        rotate_left(table,x_local->parent);
        w = x_local->parent->right;
      }
      if ((w->left->color == '\x01') && (w->right->color == '\x01')) {
        w->color = '\0';
        x_local = x_local->parent;
      }
      else {
        if (w->right->color == '\x01') {
          w->left->color = '\x01';
          w->color = '\0';
          rotate_right(table,w);
          w = x_local->parent->right;
        }
        w->color = x_local->parent->color;
        x_local->parent->color = '\x01';
        w->right->color = '\x01';
        rotate_left(table,x_local->parent);
        x_local = table->root;
      }
    }
    else {
      w = x_local->parent->left;
      if (w->color == '\0') {
        w->color = '\x01';
        x_local->parent->color = '\0';
        rotate_right(table,x_local->parent);
        w = x_local->parent->left;
      }
      if ((w->right->color == '\x01') && (w->left->color == '\x01')) {
        w->color = '\0';
        x_local = x_local->parent;
      }
      else {
        if (w->left->color == '\x01') {
          w->right->color = '\x01';
          w->color = '\0';
          rotate_left(table,w);
          w = x_local->parent->left;
        }
        w->color = x_local->parent->color;
        x_local->parent->color = '\x01';
        w->left->color = '\x01';
        rotate_right(table,x_local->parent);
        x_local = table->root;
      }
    }
  }
  x_local->color = '\x01';
  return;
}