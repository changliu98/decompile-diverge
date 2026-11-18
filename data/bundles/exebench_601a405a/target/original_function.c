void simple_sort_swapper(int* one, int* two) {
    int aux = *one;
    *one = *two;
    *two = aux;
}