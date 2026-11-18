char** func0(char** arr1, int n1, char** arr2, int n2) {
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += strlen(arr1[i]);
    }
    for (int i = 0; i < n2; i++) {
        sum2 += strlen(arr2[i]);
    }
    if (sum1 < sum2) {
        return arr1;
    } else if (sum1 > sum2) {
        return arr2;
    } else {
        return arr1;
    }
}