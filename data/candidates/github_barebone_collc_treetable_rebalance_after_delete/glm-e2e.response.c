void rebalance_after_delete(struct Node **root, struct Node *node) {
    while (node != *root && node->color == 1) {
        if (node == node->parent->left) {
            struct Node *sibling = node->parent->right;
            if (sibling->color == 0) {
                sibling->color = 1;
                node->parent->color = 0;
                rotate_left(root, node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == 1 && sibling->right->color == 1) {
                sibling->color = 0;
                node = node->parent;
            } else {
                if (sibling->right->color == 1) {
                    sibling->left->color = 1;
                    sibling->color = 0;
                    rotate_right(root, sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = 1;
                sibling->right->color = 1;
                rotate_left(root, node->parent);
                node = *root;
            }
        } else {
            struct Node *sibling = node->parent->left;
            if (sibling->color == 0) {
                sibling->color = 1;
                node->parent->color = 0;
                rotate_right(root, node->parent);
                sibling = node->parent->left;
            }
            if (sibling->right->color == 1 && sibling->left->color == 1) {
                sibling->color = 0;
                node = node->parent;
            } else {
                if (sibling->left->color == 1) {
                    sibling->right->color = 1;
                    sibling->color = 0;
                    rotate_left(root, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = 1;
                sibling->left->color = 1;
                rotate_right(root, node->parent);
                node = *root;
            }
        }
    }
    node->color = 1;
}