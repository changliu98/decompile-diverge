void sort4_sorting_network_simple_swap(short *arr) {
    // Step 1: Compare and swap arr[0] and arr[1]
    if (arr[0] < arr[1]) {
        short temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }

    // Step 2: Compare and swap arr[2] and arr[3]
    if (arr[2] < arr[3]) {
        short temp = arr[2];
        arr[2] = arr[3];
        arr[3] = temp;
    }

    // Step 3: Compare and swap arr[0] and arr[2]
    if (arr[0] < arr[2]) {
        short temp = arr[0];
        arr[0] = arr[2];
        arr[2] = temp;
    }

    // Step 4: Compare and swap arr[1] and arr[3]
    if (arr[1] < arr[3]) {
        short temp = arr[1];
        arr[1] = arr[3];
        arr[3] = temp;
    }

    // Step 5: Compare and swap arr[1] and arr[2]
    if (arr[1] < arr[2]) {
        short temp = arr[1];
        arr[1] = arr[2];
        arr[2] = temp;
    }
}