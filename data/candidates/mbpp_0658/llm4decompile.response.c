int func0(int *list1, int length) {
    int i, j;
    int result;
    int max_val = 0;
    int occu;
    result = list1[0];
    for (i = 0; i < length; i++) {
        occu = 0;
        for (j = 0; j < length; j++) {
            if (list1[j] == list1[i])
                occu++;
        }
        if (occu > max_val) {
            max_val = occu;
            result = list1[i];
        }
    }
    return result;
}