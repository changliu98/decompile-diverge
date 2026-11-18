int func0(int *arr1, int n1, int *arr2, int n2) {
    unsigned char lookup[1000];
    memset(lookup, 0, 1000);

    for (int i = 0; i < n1; i++) {
        lookup[arr1[i]] = 1;
    }

    for (int i = 0; i < n2; i++) {
        if (!lookup[arr2[i]]) {
            return 0;
        }
    }
    
    return 1;
}