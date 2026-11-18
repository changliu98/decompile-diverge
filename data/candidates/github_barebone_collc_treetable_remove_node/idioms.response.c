void remove_node(struct CC_TreeTable *table, struct CC_Tree *node)
{
    struct CC_Tree *x;
    int x_color = node->color;
    if (node->left == table->sentinel) {
        x = node->right;
        tree_transplant(table, node, x);
    } else if (node->right == table->sentinel) {
        x = node->left;
        tree_transplant(table, node, x);
    } else {
        struct CC_Tree *y = tree_minimum(table, node->right);
        x_color = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            tree_transplant(table, y, y->right);
            y->right = node->right;
            y->right->parent = y;
            tree_transplant(table, node, y);
            y->left = node->left;
            y->left->parent = y;
        }
        tree_transplant(table, node, y);
        y->color = node->color;
    }
    if (x_color == 1) {
        tree_delete_fixup(table, x);
    }
    table->mem_free(node);
    --table->size;
}