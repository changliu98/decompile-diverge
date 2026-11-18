void remove_node(TreeTable *table, RBNode *z) {
    RBNode *x;
    RBNode *y = z;
    int y_color = (int8_t)z->color;

    // Case 1: Node to remove has no left child
    if (z->left == table->dummy) {
        x = z->right;
        rotate_left(table, z, z->right);
    } 
    // Case 2: Node to remove has no right child
    else if (z->right == table->dummy) {
        x = z->left;
        rotate_right(table, z, z->left);
    } 
    // Case 3: Node has two children
    else {
        // Find the in-order successor
        y = rotate_right(table, z, z->right);
        y_color = (int8_t)y->color;
        x = y->right;

        // If the successor is the direct right child of z
        if (y->parent == z) {
            x->parent = y;
        } else {
            // Transplant the successor
            rotate_left(table, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        // Transplant z with y
        rebalance_after_delete(table, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    // If the removed/transplanted node was black, fix the tree properties
    if (y_color == 1) {
        rebalance_after_delete(table, x, x);
    }

    // Free the removed node's memory
    table->free(z);

    // Decrement the tree size
    table->size--;
}