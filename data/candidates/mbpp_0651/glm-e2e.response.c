bool func0(int *arr1, int arr1_size, int *arr2, int arr2_size) {
    for (int i = 0; i < arr2_size; i++) {
        bool found = false;
        for (int j = 0; j < arr1_size; j++) {
            if (arr2[i] == arr1[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}