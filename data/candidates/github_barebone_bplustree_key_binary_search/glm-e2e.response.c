int key_binary_search(void* node, int key) {
    int* keys = (int*)((char*)node + 0x28);
    int high;
    
    if (is_leaf(node)) {
        high = *((int*)((char*)node + 0x24));
    } else {
        high = *((int*)((char*)node + 0x24)) - 1;
    }
    
    int low = -1;
    
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (key > keys[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }
    
    if (high < *((int*)((char*)node + 0x24)) && keys[high] == key) {
        return high;
    } else {
        return -high - 1;
    }
}