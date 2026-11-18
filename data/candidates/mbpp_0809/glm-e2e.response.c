bool func0(int *arr1, int *arr2, int size) {
    bool is_greater = true;
    for (int i = 0; i < size; i++) {
        if (arr1[i] <= arr2[i]) {
            is_greater = false;
            break;
        }
    }
    return is_greater;
}