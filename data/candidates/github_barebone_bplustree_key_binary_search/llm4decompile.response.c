int key_binary_search(bplus_node *node, key_t target)
{
    int high;
    int low;
    int mid;
    int len;
    key_t *arr;

    len = is_leaf(node) ? node->children : node->children - 1;
    arr = (key_t *)&node[1];

    low = -1;
    high = len;
    while (low + 1 < high) {
        mid = low + (high - low) / 2;
        if (arr[mid] < target)
            low = mid;
        else
            high = mid;
    }

    if (high < len && arr[high] == target)
        return high;
    else
        return -(high + 1);
}