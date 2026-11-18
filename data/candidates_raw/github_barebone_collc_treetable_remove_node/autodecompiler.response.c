void remove_node(struct clib_rb* pTree,struct clib_rb_node* node) {
    struct clib_rb_node* y=node;
    int y_is_black=y->color;
    struct clib_rb_node* x;

    if (node->left == pTree->sentinel) {
        x=node->right;
        transplant(pTree,node,node->right);
    } else if (node->right == pTree->sentinel) {
        x=node->left;
        transplant(pTree,node,node->left);
    } else {

        y=tree_min(node->right);
        y_is_black=y->color;
        x=y->right;

        if (y->parent == node) {
            x->parent=y;
        } else {
            transplant(pTree,y,y->right);
            y->right=node->right;
            y->right->parent=y;
        }
        transplant(pTree,node,y);
        y->left=node->left;
        y->left->parent=y;
        y->color=node->color;
    }

    if (y_is_black==1)
        rebalance_after_delete(pTree,x);

    pTree->free(node);
    pTree->count--;
}