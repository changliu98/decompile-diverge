void combain_sorted_array(int *arr1, int *arr2, int *out) {
    int *end1 = arr1 + 5;
    int *end2 = arr2 + 5;
    
    while (arr1 < end1 && arr2 < end2) {
        if (*arr1 > *arr2) {
            if (arr2 == end2 - 1) {
                *out = *arr2;
                out++;
                while (arr1 < end1) {
                    *out = *arr1;
                    arr1++;
                    out++;
                }
                break;
            } else {
                *out = *arr2;
                arr2++;
                out++;
            }
        } else {
            if (arr1 == end1 - 1) {
                *out = *arr1;
                out++;
                while (arr2 < end2) {
                    *out = *arr2;
                    arr2++;
                    out++;
                }
                break;
            } else {
                *out = *arr1;
                arr1++;
                out++;
            }
        }
    }
}