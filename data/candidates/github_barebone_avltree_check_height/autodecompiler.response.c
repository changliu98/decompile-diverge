int check_height(struct bt_node *root, struct bt_node *node) {
    int lh, rh, b, h;
    if (node == &root->nil) {
        h = 0;
    } else {
        lh = check_height(root, node->left);
        if (lh < 0)
            h = lh;

        rh = check_height(root, node->right);
        if (rh < 0)
            h = rh;

        b = rh - lh;
        if (b > 1 || b < -1 || b != node->balance) {
            h = -1;
        } else {
            h = (lh > rh ? lh : rh) + 1;
        }
    }
    return h;
}