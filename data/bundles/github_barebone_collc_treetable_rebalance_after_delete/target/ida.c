void __cdecl rebalance_after_delete(CC_TreeTable *table, RBNode *x)
{
  bool v2; // [rsp+7h] [rbp-19h]
  RBNode *w; // [rsp+8h] [rbp-18h]
  RBNode *wa; // [rsp+8h] [rbp-18h]

  while ( 1 )
  {
    v2 = 0;
    if ( x != table->root )
      v2 = x->color == 1;
    if ( !v2 )
      break;
    if ( x == x->parent->left )
    {
      w = x->parent->right;
      if ( !w->color )
      {
        w->color = 1;
        x->parent->color = 0;
        rotate_left(table, x->parent);
        w = x->parent->right;
      }
      if ( w->left->color == 1 && w->right->color == 1 )
      {
        w->color = 0;
        x = x->parent;
      }
      else
      {
        if ( w->right->color == 1 )
        {
          w->left->color = 1;
          w->color = 0;
          rotate_right(table, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 1;
        w->right->color = 1;
        rotate_left(table, x->parent);
        x = table->root;
      }
    }
    else
    {
      wa = x->parent->left;
      if ( !wa->color )
      {
        wa->color = 1;
        x->parent->color = 0;
        rotate_right(table, x->parent);
        wa = x->parent->left;
      }
      if ( wa->right->color == 1 && wa->left->color == 1 )
      {
        wa->color = 0;
        x = x->parent;
      }
      else
      {
        if ( wa->left->color == 1 )
        {
          wa->right->color = 1;
          wa->color = 0;
          rotate_left(table, wa);
          wa = x->parent->left;
        }
        wa->color = x->parent->color;
        x->parent->color = 1;
        wa->left->color = 1;
        rotate_right(table, x->parent);
        x = table->root;
      }
    }
  }
  x->color = 1;
}