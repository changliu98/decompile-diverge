int func0(struct node *root) {
    int x, y;
    if (root == NULL)
        return -1;
    else {
        x = root->data;
        if (root->left!= NULL)
            y = root->left->data;
        else
            y = -2;
        if (y == x - 1)
            return func0(root->right);
        else if (y == x - 2)
            return func0(root->left);
        else
            return 1;
    }
}