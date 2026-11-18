void stb_kdtree_search_knn_recursive(struct btreeNode *myNode, double key[], int pos, int *child,
             double value[], int numKeys) {
    int j;
    int split;
    double firstkey;
    struct btreeNode *newNode;

    if (myNode == NULL)
        return;

    firstkey = key[pos];
    split = -1;
    for (j = 0; j < numKeys; j++) {
        if (value[j] < firstkey || value[j] == firstkey) {
            split = j;
            break;
        }
    }

    if (split < 0) {
        for (j = numKeys - 1; j > split; j--) {
            value[j + 1] = value[j];
            child[j + 1] = child[j];
        }
        value[j + 1] = firstkey;
        child[j + 1] = myNode->link[myNode->count];
    }

    newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
    if (firstkey * firstkey > key[myNode->count - 1]) {
        stb_kdtree_search_knn_recursive(myNode->link[myNode->count], key, pos, child, value, numKeys);
    } else {
        stb_kdtree_search_knn_recursive(myNode->link[0], key, pos, child, value, numKeys);
    }
}