static void remove_node(CC_TreeTable *table, RBNode *z)
{
    RBNode *x;
    RBNode *y = z;

    int y_color = y->color;

    if (z->left == table->sentinel) {
        x = z->right;
        transplant(table, z, z->right);
    } else if (z->right == table->sentinel) {
        x = z->left;
        transplant(table, z, z->left);
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
    if (y_color == RB_BLACK)
        rebalance_after_delete(table, x);

    table->mem_free(z);
    table->size--;
}