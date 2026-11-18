int func0(int lst[], int size)
{
    int i;
    int sum = 0;

    for (i = 0; 2 * i + 1 < size; i++) {
        if (lst[2 * i + 1] % 2 == 0)
            sum += lst[2 * i + 1];
    }

    return sum;
}