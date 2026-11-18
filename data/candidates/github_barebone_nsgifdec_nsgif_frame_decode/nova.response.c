int nsgif_frame_decode(struct Tree *tree, int value, struct Node **node) {
    int flag = 0, i;
    if (value >= tree->count)
        flag = 3;
    else if (value == tree->root) {
        *node = tree->nodes;
        flag = 0;
    } else if (value < tree->root || tree->root == -1) {
        i = 0;
    } else {
        i = find(tree, 0, tree->root);
    }
    if (flag == 0) {
        for (; i < value; i++) {
            flag = insert(tree, i, 1);
            if (flag)
                break;
        }
    } else {
        *node = tree->nodes;
        flag = 3;
    }
    return flag;
}