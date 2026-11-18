void remove_node(CC_TreeTable *table, RBNode *z)
{
    RBNode *x;
    RBNode *y;
    int y_color;

    if (z->left == table->sentinel && z->right == table->sentinel) {
        y = z;
        x = z->right;
        y_color = y->color;
        transplant(table, y, z->right);
    } else if (z->left == table->sentinel) {
        y = z;
        x = z->right;
        y_color = y->color;
        transplant(table, y, z->right);
    } else if (z->right == table->sentinel) {
        y = z;
        x = z->left;
        y_color = y->color;
        transplant(table, y, z->left);
    } else {
        y = tree_min(table, z->right);
        y_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(table, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(table, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_color == 1) {
        rebalance_after_delete(table, x);
    }

    table->mem_free(z);
    table->size--;
}