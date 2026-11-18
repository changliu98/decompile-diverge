void array_are_reference_type(int arr[2]) {
    int temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
}