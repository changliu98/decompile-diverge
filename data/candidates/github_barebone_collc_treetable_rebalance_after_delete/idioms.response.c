void rebalance_after_delete(struct CC_TreeTable *table, struct RBNode *x)
{
  struct RBNode *y;
  for (;;)
  {
    int xred = 0;
    if (x != table->root)
      xred = (x->color == 1);
    if (!xred)
      break;
    if (x == x->parent->left)
    {
      y = x->parent->right;
      if (y->color == 0)
      {
        y->color = 1;
        x->parent->color = 0;
        RBTreeLeftRotate(table, x->parent);
        y = x->parent->right;
      }
      if (y->left->color == 1 && y->right->color == 1)
      {
        y->color = 0;
        x = x->parent;
      }
      else
      {
        if (y->right->color == 1)
        {
          y->left->color = 1;
          y->color = 0;
          RBTreeRightRotate(table, y);
          y = x->parent->right;
        }
        y->color = x->parent->color;
        x->parent->color = 1;
        y->right->color = 1;
        RBTreeLeftRotate(table, x->parent);
        x = table->root;
      }
    }
    else
    {
      y = x->parent->left;
      if (y->color == 0)
      {
        y->color = 1;
        x->parent->color = 0;
        RBTreeRightRotate(table, x->parent);
        y = x->parent->left;
      }
      if (y->right->color == 1 && y->left->color == 1)
      {
        y->color = 0;
        x = x->parent;
      }
      else
      {
        if (y->left->color == 1)
        {
          y->right->color = 1;
          y->color = 0;
          RBTreeLeftRotate(table, y);
          y = x->parent->left;
        }
        y->color = x->parent->color;
        x->parent->color = 1;
        y->left->color = 1;
        RBTreeRightRotate(table, x->parent);
        x = table->root;
      }
    }
  }
  x->color = 1;
}