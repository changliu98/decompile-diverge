void func0(int *list, int list_size) {
    int curr_size = list_size;
    while (curr_size > 1) {
        int max_index = find_max_index(list, curr_size);
        if (max_index != curr_size - 1) {
            reverse(list, 0, max_index);
            reverse(list, 0, curr_size - 1);
        }
        curr_size--;
    }
}