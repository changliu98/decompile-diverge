int add_item_to_array(struct node *tree, struct node *node) {
    struct node *temp = NULL;
    int flag = 0;

    if (node == NULL || tree == NULL || tree == node) {
        flag = 0;
    } else {
        temp = tree->parent;
        if (temp == NULL) {
            tree->parent = node;
            node->left = node;
            node->right = node;
        } else {
            if (temp->left == NULL) {
                temp->left = node;
                node->parent = tree->parent;
            } else {
                add_item_to_array(temp->left, node);
                tree->parent->left = node;
            }
        }
        flag = 1;
    }
    return flag;
}