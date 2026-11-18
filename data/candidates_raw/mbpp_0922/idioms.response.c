void max_product(int *array, int array_len, int *max_x, int *max_y)
{
    int i; int j;
    if (array_len < 2) {
        *max_x = 0;
        *max_y = 0;
        return;
    }
    *max_x = array[0];
    *max_y = array[1];
    for (i = 0; i < array_len; i++) {
        for (j = i + 1; j < array_len; j++) {
            if (array[i]*array[j] > *max_x * *max_y) {
                *max_x = array[i];
                *max_y = array[j];
            }
        }
    }
}