int func0(int *a, int n, int k) {
    int max = max_index(a, n, k);
    int min_index = 0;
    int min = 0;
    int i = 0;
    while (i < 7) {
        if (i < 7) {
            int temp = max_index(a, n, k);
            i++;
            if (temp < max) {
                min_index = i;
                max = temp;
            }
        } else {
            break;
        }
    }
    if (min_index == 0) {
        int temp = min_index(a, n, k);
        i--;
        if (temp > max) {
            min_index = i;
            max = temp;
        }
    } else {
        int temp = min_index(a, n, k);
        i++;
    }
    return min_index;
}