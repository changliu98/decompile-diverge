void iadd(int *arr, int *idx, int val) {
    int temp1 = arr[*idx];
    (*idx)--;
    int temp2 = arr[*idx];
    arr[*idx] = temp1 + temp2;
}