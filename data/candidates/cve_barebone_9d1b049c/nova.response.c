int Media_CheckDataEntry(struct Node *root, int k) {
    int result;
    struct Node *temp;
    if (root == NULL || k == 0) {
        result = -1;
    } else if (k > height(root->parent->parent->left)) {
        result = -1;
    } else {
        temp = kth_node(root->parent->parent->left, k - 1);
        if (temp == NULL) {
            result = -10;
        } else if (temp->color == RED) {
            result = 0;
        } else if (temp->key == 1970433568) {
            result = -4;
        } else {
            if (root->parent->parent->left->color == RED) {
                result = Media_CheckDataEntry(temp->parent, 0);
            } else {
                result = Media_CheckDataEntry(temp->parent, root->parent->parent->left->n);
            }
            if (result!= 0) {
                result = -1;
            }
        }
    }
    return result;
}