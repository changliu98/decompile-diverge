int heatshrink_decoder_finish(struct node *root) {
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
            return heatshrink_decoder_finish(root->right);
        else if (y == x - 2)
            return heatshrink_decoder_finish(root->left);
        else
            return 1;
    }
}