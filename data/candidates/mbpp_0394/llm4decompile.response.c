int func0(int *test_tup, int size)
{
    int temp[size];
    int temp_size = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        int found = 0;
        for (j = 0; j < temp_size; j++) {
            if (temp[j] == test_tup[i]) {
                found = 1;
                break;
            }
        }
        if (found) {
            return 0;
        }
        temp[temp_size++] = test_tup[i];
    }
    return 1;
}