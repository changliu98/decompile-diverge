int func0(int a, int b, int c)
{
    int array[] = { a, b, c };
    int counts[3];
    int i, j;
    int unique_values = 0;

    memset(counts, 0, sizeof(counts));

    for (i = 0; i < 3; i++) {
        int found = 0;

        for (j = 0; j < i; j++) {
            if (array[j] == array[i]) {
                found = 1;
                break;
            }
        }

        if (!found)
            unique_values++;
    }

    if (unique_values == 3)
        return 0;
    else
        return 4 - unique_values;
}