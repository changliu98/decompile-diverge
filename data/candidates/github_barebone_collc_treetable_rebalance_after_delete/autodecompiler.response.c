void rebalance_after_delete(AVLNode** avl, AVLNode* node) {
 while (1) {
  char left;
  if (node == *avl || node->left == NULL)
   left = 0;
  else
   left = node->left->height == 1;

  if (left & 1) {
   AVLNode* tmp = node->right;
   if (tmp->height == 0) {
    tmp->height = 1;
    node->right->height = 0;
    rotate_left(avl, node->right);
    tmp = node->right->left;
   }
   if (tmp->left->height == 1 && tmp->right->height == 1) {
    tmp->height = 0;
    node = node->right;
   } else if (tmp->right->height == 1) {
    tmp->left->height = 1;
    tmp->height = 0;
    rotate_right(avl, tmp);
    tmp = node->right->left;
   } else {
    tmp->height = node->right->height;
    node->right->height = 1;
    tmp->left->height = 1;
    rotate_left(avl, node->right);
    node = *avl;
   }
  } else {
   AVLNode* tmp = node->left;
   if (tmp->height == 0) {
    tmp->height = 1;
    node->left->height = 0;
    rotate_right(avl, node->left);
    tmp = node->left->right;
   }
   if (tmp->right->height == 1 && tmp->left->height == 1) {
    tmp->height = 0;
    node = node->left;
   } else if (tmp->left->height == 1) {
    tmp->right->height = 1;
    tmp->height = 0;
    rotate_left(avl, tmp);
    tmp = node->left->right;
   } else {
    tmp->height = node->left->height;
    node->left->height = 1;
    tmp->right->height = 1;
    rotate_right(avl, node->left);
    node = *avl;
   }
  }
  if (!left)
   break;
 }
 node->height = 1;
}