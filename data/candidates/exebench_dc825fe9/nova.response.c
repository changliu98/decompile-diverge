void summary(int *arr, int size, double *pos, double *neg, double *zer) {
    int pos_count = 0, neg_count = 0, zer_count = 0;
    for (int i = 0; i < size; i++) {
        switch (arr[i]) {
        case 0:
            zer_count++;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            pos_count++;
            break;
        default:
            neg_count++;
            break;
        }
    }
    *pos = (double)pos_count / size;
    *neg = (double)neg_count / size;
    *zer = (double)zer_count / size;
}