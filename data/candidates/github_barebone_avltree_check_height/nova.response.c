int check_height(char *s, struct node *root) {
    int i, j, k, l;
    if (root == s + 64) {
        i = 0;
    } else {
        i = check_height(s, root->lchild);
        if (i < 1) {
            i = check_height(s, root->rchild);
            if (i < 1) {
                return i;
            } else {
                j = i;
                if (j - 1 < 0 || j - 1 > 1 || root->rchild->element!= s[24]) {
                    i = -1;
                }
            }
        } else {
            if (i > check_height(s, root->rchild)) {
                k = i;
            } else {
                k = check_height(s, root->rchild);
            }
            i = k + 1;
        }
    }
    return i;
}