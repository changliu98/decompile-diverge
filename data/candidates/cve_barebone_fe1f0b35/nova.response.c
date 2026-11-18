int GetHintFormat(struct node *root) {
    struct node *temp = root->left->left->left;
    int GetHintFormat;
    if (strcmp(temp->data, "+")!= 0) {
        GetHintFormat = 0;
    } else {
        if (temp!= NULL && temp->count == 0) {
            struct node *temp1 = find(root->left->left->right, NULL);
            if (temp == NULL) {
                GetHintFormat = temp1->count;
            } else {
                if (temp1!= NULL) {
                    temp->count = temp1->count;
                    GetHintFormat = temp->count;
                } else {
                    GetHintFormat = temp->count;
                }
            }
        } else {
            GetHintFormat = temp->count;
        }
    }
    return GetHintFormat;
}