void rebalance_after_delete(CC_TreeTable *table, RBNode *x)
{
    RBNode *sibling;

    while (x != table->root && x->color == (1)) {
        if (x == x->parent->left) {
            sibling = x->parent->right;

            if (sibling->color == (0)) {
                sibling->color = (1);
                x->parent->color = (0);
                rotate_left(table, x->parent);
                sibling = x->parent->right;
            }

            if (sibling->left->color == (1) && sibling->right->color == (1)) {
                sibling->color = (0);
                x = x->parent;
            } else {
                if (sibling->right->color == (1)) {
                    sibling->left->color = (1);
                    sibling->color = (0);
                    rotate_right(table, sibling);
                    sibling = x->parent->right;
                }

                sibling->color = x->parent->color;
                x->parent->color = (1);
                sibling->right->color = (1);
                rotate_left(table, x->parent);
                x = table->root;
            }
        } else {
            sibling = x->parent->left;

            if (sibling->color == (0)) {
                sibling->color = (1);
                x->parent->color = (0);
                rotate_right(table, x->parent);
                sibling = x->parent->left;
            }

            if (sibling->right->color == (1) && sibling->left->color == (1)) {
                sibling->color = (0);
                x = x->parent;
            } else {
                if (sibling->left->color == (1)) {
                    sibling->right->color = (1);
                    sibling->color = (0);
                    rotate_left(table, sibling);
                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = (1);
                sibling->left->color = (1);
                rotate_right(table, x->parent);
                x = table->root;
            }
        }
    }
    x->color = (1);
}