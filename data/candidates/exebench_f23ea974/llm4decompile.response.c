void array_are_reference_type(int *arr[]) {
    int tmp = *arr[0];
    *arr[0] = *arr[1];
    *arr[1] = tmp;
}