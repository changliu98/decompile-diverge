int func0(char *s, struct node *root) {
    int i, j, k, l;
    if (root == s + 64) {
        i = 0;
    } else {
        i = func0(s, root->lchild);
        if (i < 1) {
            i = func0(s, root->rchild);
            if (i < 1) {
                return i;
            } else {
                j = i;
                if (j - 1 < 0 || j - 1 > 1 || root->rchild->element!= s[24]) {
                    i = -1;
                }
            }
        } else {
            if (i > func0(s, root->rchild)) {
                k = i;
            } else {
                k = func0(s, root->rchild);
            }
            i = k + 1;
        }
    }
    return i;
}