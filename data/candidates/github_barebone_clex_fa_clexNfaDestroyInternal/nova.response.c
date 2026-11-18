void clexNfaDestroyInternal(struct Node *root, char *word) {
    if (root == NULL)
        return;
    if (strlen(word) % 2 == 0)
        return;
    if (strlen(word) % 2!= 0) {
        for (size_t i = 0; i < root->count; i++) {
            if (root->p[i] == NULL)
                continue;
            clexNfaDestroyInternal(root->p[i], word);
            freeNode(root->p[i]);
        }
    }
    if (root->isLeaf) {
        free(root->word);
        free(root->word);
    }
    free(root->p);
    free(root);
}