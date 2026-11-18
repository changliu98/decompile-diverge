void addItemToBag(int *bag, int *item, int size) {
    for (int i = 0; i < size; i++) {
        item[i] -= bag[i];
    }
}